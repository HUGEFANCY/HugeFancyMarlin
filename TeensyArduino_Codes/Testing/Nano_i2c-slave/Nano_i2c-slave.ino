#include <Wire.h>

#define ANSWERSIZE 3

String answer = "PAM";

void setup() {
  Wire.begin(9);
  Wire.onRequest(requestEvent); // data request to slave
  Wire.onReceive(receiveEvent); // data slave received
  Serial.begin(9600);
  Serial.println("I2C Slave ready!");
}

void receiveEvent(int countToRead) {
  while (0 < Wire.available()) {
    byte x = Wire.read();
  }
  Serial.println("Receive event");
}

void requestEvent() {
  byte response[ANSWERSIZE];
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response,sizeof(response));
  Serial.println("Request event");
}

void loop() {
  delay(50);
}