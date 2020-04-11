const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A2;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;        // value read from the pot

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(analogInPin);
  sensorValue2 = analogRead(analogInPin2);
  delay(200);
  Serial.print("sensor 1 = ");
  Serial.print(sensorValue);
  Serial.println("");
  Serial.print("sensor 2 = ");
  Serial.print(sensorValue2);
  Serial.println("");
}
