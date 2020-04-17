#include <Arduino.h>

int globali = 0;

void setup() 
{
  Serial.begin(9600); // serieller Monitor

  RS485_setup();

}

void loop() 
{
  //SerialTastatur_CheckKeys();

  // Sende jede Sekunde eine neue Ziffer
  globali++;
  delay(1000);
  RS485_sentSignal(globali);  
}
