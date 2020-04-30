#include <Wire.h>

#define ANSWERSIZE 2

int answer = 305;
//String answer2 = "290";
//String answer3 = "112";
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
    uint16_t sum = 0;
    while (0 < Wire.available()) {
        byte x = Wire.read();
        sum += x & 0xFF;
    }
    Serial.print("Receive event! value:");
    Serial.println(sum);
}

void requestEvent() {
  Serial.print("Request event! sending: ");
  Serial.println(answer);
  digitalWrite(LED_BUILTIN, HIGH);
  byte response[ANSWERSIZE];
  int target_temp = answer;
  if (target_temp <= 255){
        response[0] = target_temp; // Wert von 0-255°C
        response[1] = 0;
    }
    else if ((target_temp > 255) and (target_temp <= 510))
    {
        response[0] = 255;
        response[1] = target_temp - 255; // Wert von 256-510°C
    } 
    else{
        response[0]=255;
        response[1]=255;
    }
  Wire.write(response,sizeof(response));
  digitalWrite(LED_BUILTIN, LOW);

  int randincrease = random(-5,5);
  answer += randincrease;

}

void loop() {

  delay(50);
}