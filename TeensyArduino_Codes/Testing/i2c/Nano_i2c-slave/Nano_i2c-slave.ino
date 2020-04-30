#include <Wire.h>

#define ANSWERSIZE 3

String answer = "106";
String answer2 = "130";
String answer3 = "112";
int iter = 0;

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
  if(iter==0){
    Serial.println("iter = 0");
    digitalWrite(LED_BUILTIN, HIGH);
    byte response[ANSWERSIZE];
    for (byte i=0;i<ANSWERSIZE;i++) {
      response[i] = (byte)answer.charAt(i);
    }
    Wire.write(response,sizeof(response));
    Serial.println("----");
    //delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);
    
  }
  else if(iter==1){
    Serial.println("iter = 1");
    digitalWrite(LED_BUILTIN, HIGH);
    byte response[ANSWERSIZE];
    for (byte i=0;i<ANSWERSIZE;i++) {
      response[i] = (byte)answer2.charAt(i);
    }
    Wire.write(response,sizeof(response));
    Serial.println("----");
    //delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);
    
  }
  else if(iter==2){
    Serial.println("iter = 2");
    digitalWrite(LED_BUILTIN, HIGH);
    byte response[ANSWERSIZE];
    for (byte i=0;i<ANSWERSIZE;i++) {
      response[i] = (byte)answer3.charAt(i);
    }
    Wire.write(response,sizeof(response));
    Serial.println("----");
    //delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);
    
  }
  else{ iter =0;}
  if (iter == 2 ){
    iter = 0;
  }
  else{
    iter++;
  }
}

void loop() {

  delay(50);
}