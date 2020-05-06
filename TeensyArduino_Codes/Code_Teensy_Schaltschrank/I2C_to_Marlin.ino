/*
 * Code responsible for communicating with Marlin via i2c.
 * The Teensy 3.5 will be designated as a slave with address 0x9 (9) 
 * The communication is done on the third i2c interface of the teensy, using pins 3 and 4.
 * 
 * Robin Godwyll April 2020
 * 
 */

//import Arduino I2C (TWIBUS) Library
#include <i2c_t3.h>
#define WIRE2_PINS   I2C_PINS_3_4  //defines SCL2 and SDA2 pins of teensy 3.5
#define ANSWERSIZE 2  //only this amount of bytes is exchanged between Marlin and this Teensy 

int target_temp_buffer = 0;

void I2C_Marlin_setup() {
    Wire2.begin(I2C_SLAVE, 0x9, WIRE2_PINS, I2C_PULLUP_EXT, 400000);         //begin i2c on pins 3+4 as slave with address 9 
    Wire2.onRequest(requestEvent);     // Function to execute on data request from master (Marlin)
    Wire2.onReceive(receiveEvent);     // Function to execute on data receive from master 
    //Serial.begin(9600);               // start serial // not necessary since it is initialised in the main .ino
    Serial.println("I2C Slave ready!");
}

/**
 * @brief reads data that is received via i2c
 * updates the target temp with the new value.  
 * @details --
 * no params no return 
 */
void receiveEvent() {    

    while (0 < Wire2.available()) {
        byte x = Wire2.read();
        target_temp_buffer += x & 0xFF;
    }
    Serial.print("Receive event! value:");
    Serial.println(target_temp_buffer);
    targetTempExtruderMarlin = target_temp_buffer;
}


/**
 * @brief answers requests form the Marlin Board. 
 * Sends 2 bytes with the current hotend temperature back to Marlin. 
 * @details --
 * no params no return 
 */
void requestEvent() {

    byte response[ANSWERSIZE];
    int target_temp = RealTempExtruderForMarlin;
    
    Serial.print("Request event! sending: ");
    Serial.println(target_temp);
    
    if (target_temp <= 255) {
            response[0] = target_temp; // Wert von 0-255°C
            response[1] = 0;
    }
    else if ((target_temp > 255) and (target_temp <= 510))  {
            response[0] = 255;
            response[1] = target_temp - 255; // Wert von 256-510°C
    } 
    else{
            response[0]=255;
            response[1]=255;
    }
    Wire2.write(response,sizeof(response)); //send value to Marlin vial i2c
}

/*void loop() {
*
*  delay(50);
*}
*/