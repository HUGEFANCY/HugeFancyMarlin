// MAX31865 https://www.adafruit.com/products/3328

#include <Adafruit_MAX31865.h>
#define debug
float temperature_oben = 0;
float temperature_unten = 0;

// PINOUT
// MAX31865 oben
const byte CS_pin_oben = 17;
// MAX31865 unten
const byte CS_pin_unten = 18;
// MAX31865 oben und unten
const byte SDI_pin = 16;
const byte SDO_pin = 15;
const byte CLK_pin = 14;

// Use software
Adafruit_MAX31865 thermo_oben = Adafruit_MAX31865(CS_pin_oben, SDI_pin, SDO_pin, CLK_pin);
Adafruit_MAX31865 thermo_unten = Adafruit_MAX31865(CS_pin_unten, SDI_pin, SDO_pin, CLK_pin);

#define RREF 430.0 // The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RNOMINAL 100.0 // The 'nominal' 0-degrees-C resistance of the sensor // 100.0 for PT100, 1000.0 for PT1000

Metro temperaturIntervall = Metro(500);


void setup_PT100_MAX31865()
{
  thermo_oben.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo_unten.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
}



void loop_PT100_MAX31865()
{

  if (temperaturIntervall.check() == 1)  // check if the metro has passed its interval
  {
    // Check and print any faults
    uint8_t fault = thermo_oben.readFault();
    if (fault)
    {
      Serial.print("Fault 0x"); Serial.println(fault, HEX);
      if (fault & MAX31865_FAULT_HIGHTHRESH) {
        Serial.println("RTD High Threshold");
      }
      if (fault & MAX31865_FAULT_LOWTHRESH) {
        Serial.println("RTD Low Threshold");
      }
      if (fault & MAX31865_FAULT_REFINLOW) {
        Serial.println("REFIN- > 0.85 x Bias");
      }
      if (fault & MAX31865_FAULT_REFINHIGH) {
        Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_RTDINLOW) {
        Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_OVUV) {
        Serial.println("Under/Over voltage");
      }
      thermo_oben.clearFault();
    }
    else
    {
      temperature_oben = thermo_oben.temperature(RNOMINAL, RREF);
      temperature_unten = thermo_unten.temperature(RNOMINAL, RREF);
      Serial.print("T1 = "); Serial.println(temperature_oben);
      Serial.print("T1 = "); Serial.println(temperature_unten);
      Serial.println();
    }
  }
}
