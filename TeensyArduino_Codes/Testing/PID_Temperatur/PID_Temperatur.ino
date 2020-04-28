#include <Metro.h> // Include the Metro library // https://www.pjrc.com/teensy/td_libs_Metro.html


//const int analogOutPin2 = A22; // Analog output pin that will write the resistance
const int ledPin = LED_BUILTIN;



void setup()
{
  Serial.begin(9600);
  delay(100);

  setup_PT100_MAX31865();
  setup_relays();

  pinMode(ledPin, OUTPUT);



  digitalWrite(ledPin, LOW);

  Serial.println("Setup finished");
}

void loop()

{
 
  loop_PT100_MAX31865();
  //relay_clickCluck();


  SerialTastatur_CheckKeys();
}
