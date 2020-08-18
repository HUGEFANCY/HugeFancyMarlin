
#include "inc/MarlinConfig.h"
#include "i2c_temperature_control.h"

#include "feature/twibus.h"
   TWIBus i2c_c;



boolean I2C_TempControl::send_target_temp(uint16_t target_temperature) 
{
  
    const uint8_t bufferSize = 2;
    uint8_t buffer[bufferSize]={};
    uint16_t target_temp = target_temperature;
    //SERIAL_ECHOLNPAIR("target_temp: ", target_temp);      // print 
    if (target_temp <= 255)
    {
        buffer[0] = target_temp; // Wert von 0-255°C
        buffer[1] = 0;
    }
    else if ((target_temp > 255) and (target_temp <= 510))
    {
        buffer[0] = 255;
        buffer[1] = target_temp - 255; // Wert von 256-510°C
    } 
    //SERIAL_ECHOLN("sending target temp via i2c!");      // print 
    i2c_c.address(I2C_REMOTE_ADDRESS);
    //uint16_t sum = 0;
    //sum = buffer[0] + buffer[1];
    //SERIAL_ECHOLNPAIR("target sum to send:    ", sum);      // print 

    i2c_c.addbytes_as_bytes(&buffer[0],2);
    i2c_c.send();
    //SERIAL_ECHOLN("i2c target temp sent ------- ");      // print 
    return 1;
}

uint16_t I2C_TempControl::request_hotend_temp() 
{
    //SERIAL_ECHOLNPAIR("request on hotend:",target_hotend);
    i2c_c.address(I2C_REMOTE_ADDRESS);
    int req_bytes = 2;    //number of bytes to request
    uint16_t temp = 0; 
    for (uint8_t tries = 1; tries <= 2; tries++) 
    {
        if (i2c_c.request(req_bytes)){              // Request req_bytes number of bytes
            char answer[req_bytes]={};              // a buffer to store the reply
            answer[sizeof(answer)] = 0;             //null termination of array
            i2c_c.capture(&answer[0], req_bytes);    // Get the reply  
            
            //SERIAL_ECHOLNPAIR("answer:", answer);
            //SERIAL_ECHOLNPAIR("size-of-answer:",sizeof(answer));

            for (uint8_t i = 0; i < (sizeof(answer)); i++) 
            {
                //SERIAL_ECHOLNPAIR("sum addition: ", answer[i] & 0xFF);
                temp += answer[i] & 0xFF;    //needed to make a valid int 
            }
            //SERIAL_ECHOLN("----------");
            //SERIAL_ECHOLNPAIR("int received temp:",temp);// print integer value of the received string just to check 
        }
        return temp;
    //SERIAL_ECHOLNPAIR("request failed tries left:",tries);
    }
    return temp;
}