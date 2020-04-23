



//const int analogOutPin2 = A22; // Analog output pin that will write the resistance
const int ledPin = LED_BUILTIN;



void setup() 
{
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() 
{
}
