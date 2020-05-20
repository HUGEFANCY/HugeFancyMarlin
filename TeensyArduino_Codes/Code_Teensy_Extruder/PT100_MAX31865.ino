// MAX31865 https://www.adafruit.com/products/3328

#include <Adafruit_MAX31865.h>
#define debug

// PINOUT
// MAX31865 oben
const byte CS_pin_zone_1 = 17;
// MAX31865 unten
const byte CS_pin_zone_2 = 20;
// MAX31865 oben und unten
const byte SDI_pin = 16;
const byte SDO_pin = 15;
const byte CLK_pin = 14;


// Use software
Adafruit_MAX31865 thermo_zone_1 = Adafruit_MAX31865(CS_pin_zone_1, SDI_pin, SDO_pin, CLK_pin);
Adafruit_MAX31865 thermo_zone_2 = Adafruit_MAX31865(CS_pin_zone_2, SDI_pin, SDO_pin, CLK_pin);

#define RREF 430.0 // The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RNOMINAL 100.0 // The 'nominal' 0-degrees-C resistance of the sensor // 100.0 for PT100, 1000.0 for PT1000

Metro temperaturIntervall = Metro(500);


void PT100_MAX31865_setup()
{



  //thermo_zone_1.autoConvert(false);
  //thermo_zone_2.autoConvert(false);

  thermo_zone_1.enable50Hz(false);
  thermo_zone_2.enable50Hz(false);

  thermo_zone_1.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo_zone_2.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary


  //thermo_zone_1.autoConvert(false);
  //thermo_zone_2.autoConvert(false);

  //thermo_zone_1.enable50Hz(true);
  //thermo_zone_2.enable50Hz(true);

  /* Configure:

    V_BIAS enabled
    Auto-conversion
    1-shot disabled
    3-wire enabled
    Fault detection:  automatic delay
    Fault status:  auto-clear
    50 Hz filter
    Low threshold:  0x0000
    High threshold:  0x7fff
  */
}



void PT100_MAX31865_loop()
{

  if (temperaturIntervall.check() == 1)  // check if the metro has passed its interval
  {
    // Check and print any faults
    uint8_t fault = thermo_zone_1.readFault();
    if (fault)
    {
      Serial.print("Fault 0x"); Serial.println(fault, HEX);
      if (fault & MAX31865_FAULT_HIGHTHRESH) {
        Serial.println("Zone 1: RTD High Threshold");
      }
      if (fault & MAX31865_FAULT_LOWTHRESH) {
        Serial.println("Zone 1: RTD Low Threshold");
      }
      if (fault & MAX31865_FAULT_REFINLOW) {
        Serial.println("Zone 1: REFIN- > 0.85 x Bias");
      }
      if (fault & MAX31865_FAULT_REFINHIGH) {
        Serial.println("Zone 1: REFIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_RTDINLOW) {
        Serial.println("Zone 1: RTDIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_OVUV) {
        Serial.println("Zone 1: Under/Over voltage");
      }
      thermo_zone_1.clearFault();
    }
    fault = thermo_zone_2.readFault();
    if (fault)
    {
      Serial.print("Fault 0x"); Serial.println(fault, HEX);
      if (fault & MAX31865_FAULT_HIGHTHRESH) {
        Serial.println("Zone 2: RTD High Threshold");
      }
      if (fault & MAX31865_FAULT_LOWTHRESH) {
        Serial.println("Zone 2: RTD Low Threshold");
      }
      if (fault & MAX31865_FAULT_REFINLOW) {
        Serial.println("Zone 2: REFIN- > 0.85 x Bias");
      }
      if (fault & MAX31865_FAULT_REFINHIGH) {
        Serial.println("Zone 2: REFIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_RTDINLOW) {
        Serial.println("Zone 2: RTDIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_OVUV) {
        Serial.println("Zone 2: Under/Over voltage");
      }
      thermo_zone_2.clearFault();
    }
    else
    {
      RealTemperatureZone_1 = round(thermo_zone_1.temperature(RNOMINAL, RREF));
      RealTemperatureZone_2 = round(thermo_zone_2.temperature(RNOMINAL, RREF));
      Serial.print("T Zone 1 = "); Serial.println(RealTemperatureZone_1);
      Serial.print("T Zone 2 = "); Serial.println(RealTemperatureZone_2);
      Serial.println();
    }
  }
}
