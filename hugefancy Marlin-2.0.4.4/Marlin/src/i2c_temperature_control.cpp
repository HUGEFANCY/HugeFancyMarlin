
#include "inc/MarlinConfig.h"
#include "i2c_temperature_control.h"

#include "feature/twibus.h"
   TWIBus i2c_c;



uint8_t I2C_TempControl::send_target_temp(uint8_t target_hotend,uint8_t target_temperature) {
  
    const uint8_t bufferSize = 2;
    uint8_t buffer[bufferSize];
    int target_temp = target_temperature;
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
    else{
        buffer[0]=255;
        buffer[1]=255;
    }
    SERIAL_ECHOLN("i2c temp send ");      // print 
    i2c_c.address(I2C_REMOTE_ADDRESS);
    uint16_t sum = 0;
    uint8_t result = 0;
    sum = buffer[0] + buffer[1];
    result = sum & 0xFF;
    SERIAL_ECHOLNPAIR("target buffer ", result);      // print 

    i2c_c.addbytes_as_bytes(&buffer[0],2);
    i2c_c.send();
    SERIAL_ECHOLN("--------- i2c sent ------- ");      // print 
    return 1;
        
}

uint8_t I2C_TempControl::request_hotend_temp(uint8_t target_hotend) {
  
    i2c_c.address(I2C_REMOTE_ADDRESS);
    int req_bytes = 3;    //number of bytes to request
    uint16_t temp = 999; 
    for (uint8_t tries=5; tries--;) {
        if (i2c_c.request(req_bytes)){              // Request req_bytes number of bytes
            char answer[req_bytes]={};              // a buffer to store the reply
            answer[sizeof(answer)] = 0;             //null termination of array
            i2c_c.capture(&answer[0], req_bytes);    // Get the reply  
            
            SERIAL_ECHOLN("answer:");
            SERIAL_ECHOLN(answer);
            SERIAL_ECHOLNPAIR("size of answer:",sizeof(answer));
            //SERIAL_ECHOLN(answer[]);
            for( unsigned int a = 0; a < (sizeof(answer)/sizeof(answer[0])+1); a = a + 1 ){
                //SERIAL_ECHOLN(answer[a]);   //Print reply line by line 
            }
            SERIAL_ECHOLN("----------");
            temp = atoi(answer);  // convert the received tempereture from array of chars to int
            SERIAL_ECHOLNPAIR("int received temp:",temp);// print integer value of the received string just to check 
            //temp_hotend[0].celsius = temp;      //update hotend temperature

            return temp;
        }

    }
    return temp;
}