#include <Wire.h>

#define ANSWERSIZE 3

String answer = "PAM";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(9);
  Wire.onRequest(requestEvent); // data request to slave
  Wire.onReceive(receiveEvent); // data slave received
  Serial.begin(9600);
  Serial.println("I2C Slave ready!");
}

void receiveEvent(int countToRead) {
  digitalWrite(LED_BUILTIN, HIGH);
  while (0 < Wire.available()) {
    byte x = Wire.read();
    Serial.println(x);
  }
  Serial.println("Receive event");
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
}

void requestEvent() {
  Serial.println("Request event");
  digitalWrite(LED_BUILTIN, HIGH);
  byte response[ANSWERSIZE];
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response,sizeof(response));
  Serial.println("Request event");
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  delay(50);
}