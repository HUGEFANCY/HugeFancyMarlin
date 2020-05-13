/*
        DIY Arduino based RC Transmitter
  by Dejan Nedelkovski, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/


#include <Metro.h> //Include Metro library




void setup() {
  Serial.begin(9600);
  delay(100);

  setupInputs();
  setupSerialDataOutput();
  setupOled();

  // Call this function if you need to get the IMU error values for your module
  //calculate_IMU_error();
 

  Serial.println("Setup end");
   loopOled();

}


void loop()
{
  loopInputs();
  loopSerialDataOutput();
 

  // Send the whole data from the structure to the receiver
  //radio.write(&data, sizeof(Data_Package));
}
