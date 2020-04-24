#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C Master ready!");
}

void loop() {
  delay(50);
  Serial.println("Write data");
  Wire.beginTransmission(9);
  Wire.write(0);
  Wire.endTransmission();
  Serial.println("Receive data");
  Wire.requestFrom(9,3);
  String response = "";
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
  }
  Serial.println(response);
}