
/*
   Code responsible for communicating with Marlin via i2c.
   The Teensy 3.5 will be designated as a slave with address 0x9 (9)
   The communication is done on the third i2c interface of the teensy, using pins 3 and 4.

   Robin Godwyll April 2020

*/

//import Arduino I2C (TWIBUS) Library
#include <i2c_t3.h>
#define WIRE2_PINS   I2C_PINS_3_4  // defines SCL2 and SDA2 pins of teensy 3.5
#define ANSWERSIZE 2  // only this amount of bytes is exchanged between Marlin and this Teensy 

int target_temp_buffer = 0;
const uint8_t temp_header = 11;
const uint8_t fan_header = 12;
const uint8_t col_onetime_header = 13;
const uint8_t col_periodisch_header = 14;

void I2C_Marlin_setup()
{
  Wire2.begin(I2C_SLAVE, 0x9, WIRE2_PINS, I2C_PULLUP_EXT, 100000); // NEU !! vorher 400000 ###// begin i2c on pins 3+4 as slave with address 9
  Wire2.onRequest(requestEvent); // Function to execute on data request from master (Marlin)
  Wire2.onReceive(receiveEvent); // Function to execute on data receive from master
  Serial.println("I2C Slave ready!");
}


/**
   @brief reads data that is received via i2c
   updates the target temp with the new value.
   @details --
   no params no return
*/
void receiveEvent()
{
  uint8_t counter = 0;
  byte i2c_header;

  byte col_click_value[2] = {0}; // Array Länge [2] 0,1
  byte col_metronome_value[3] = {0};
  
  while (0 < Wire2.available())
  {
    
    
    if (counter == 0)
    {
      i2c_header = Wire2.read();
      counter++;
      Serial.print("Header of receiveEvent:  ");
      Serial.println(i2c_header);
      continue;
    }

    if (i2c_header == temp_header)
    {
      byte x = Wire2.read();
      target_temp_buffer += x & 0xFF;
    }
    else if (i2c_header == fan_header)
    {
      byte x = Wire2.read();
      PwmValuePartCoolingFanMarlin = x & 0xFF;
      Serial.print("PWM for fans set:  "); Serial.println(PwmValuePartCoolingFanMarlin);
    }
    else if (i2c_header == col_onetime_header)
    {
      byte x = Wire2.read();
      
      col_click_value[counter - 1] = x; // x & 0xFF;
      Serial.print("Color: "); Serial.println(col_click_value[counter - 1]);
      if (counter == 2)
      {
        RS485_Schaltschrank_Send_clickColor(col_click_value[0], col_click_value[1]);
        Serial.print("color clicks set:  "); Serial.println(col_click_value[0] + col_click_value[1]);
      }
    }
    else if (i2c_header == col_periodisch_header)
    {
      byte x = Wire2.read();

      col_metronome_value[counter - 1] = x & 0xFF;
      Serial.print("color: "); Serial.println(col_metronome_value[counter - 1]);

      if (counter == 2)
      {
        RS485_Schaltschrank_Send_metronomeColor(col_metronome_value[0], col_metronome_value[1], col_metronome_value[2]);
        Serial.print("color clicks set:  "); Serial.println(col_metronome_value[0] + col_metronome_value[1] + col_metronome_value[2]);
      }
    }
    else
    {
      Serial.print("Header not recognized");Serial.println(i2c_header);
    }
    counter++;
  }
  Serial.print("- - - Bekommen von Marlin: target_temp_buffer = "); Serial.println(target_temp_buffer);
  TargetTempExtruderMarlin = target_temp_buffer;
  target_temp_buffer = 0;
  RGB_Blau();
  RGB_Aus();
}


/**
   @brief answers requests form the Marlin Board.
   Sends 2 bytes with the current hotend temperature back to Marlin.
   @details --
   no params no return
*/
void requestEvent()
{
  //Serial.print("+ + + CombinedRealTempExtruder = ");Serial.println(CombinedRealTempExtruder);

  byte response[ANSWERSIZE];
  int real_temp = CombinedRealTempExtruder;

  //Serial.print("Request event! sending: ");
  //Serial.println(target_temp);

  if (real_temp <= 255) {
    response[0] = real_temp; // Wert von 0-255°C
    response[1] = 0;
  }
  else if ((real_temp > 255) and (real_temp <= 510))  {
    response[0] = 255;
    response[1] = real_temp - 255; // Wert von 256-510°C
  }
  /*
    else {
    response[0] = 255;
    response[1] = 255;
    }
  */
  Wire2.write(response, sizeof(response)); //send value to Marlin vial i2c
  Serial.print("+ + + Gesendet zu Marlin: real_temp = "); Serial.println(real_temp);
  RGB_Rot();
  RGB_Aus();
}
