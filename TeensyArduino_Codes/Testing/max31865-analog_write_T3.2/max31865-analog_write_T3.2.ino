/*************************************************** 
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_MAX31865.h>

// Use software SPI: 17-CS, 16-DI, 15-DO, 14-CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(17, 16, 15, 14);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// Define an Analog output pin which will send the temperature values
const int analogOutPin = A14; // Analog output pin which will write temperature
const int analogInPin = A4; // Analog input pin which will read temperature value
int analog_resolution = 12; // sets resolution of analog writing as exponent of 2 (2^12=4096)
//this is done further down: analogWriteRes(analog_resolution); // Set the analog output resolution to 12 bit (4096 levels).
int max_temp = 400;

//const int analogOutPin2 = A22; // Analog output pin that will write the resistance
const int ledPin = LED_BUILTIN;

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void setup() {
  analogWriteRes(analog_resolution); // Set the analog output resolution to 12 bit (4096 levels).
  analogReadResolution(analog_resolution);
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
}


void loop() {
  uint16_t rtd = thermo.readRTD();

  //Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  float temperature = thermo.temperature(RNOMINAL, RREF);
  float resistance = RREF*ratio;
  float maxtemp_ratio = temperature / max_temp;

  float temp_to_write = (pow(2,analog_resolution)*maxtemp_ratio);
  analogWrite(analogOutPin, temp_to_write);
  float analogIn = analogRead(analogInPin);
  float temp_read = analogIn / pow(2,12)* max_temp;
  
  //analogWrite(analogOutPin2, resistance);
  
  //Serial.print("Ratio = "); Serial.println(ratio,8);
  Serial.print("temp to write = "); Serial.println(temp_to_write);
    Serial.print("temp read = "); Serial.println(temp_read);
  Serial.print("Ratio of Max temperature = "); Serial.println(maxtemp_ratio);
  Serial.print("Resistance = "); Serial.println(RREF*ratio);
  Serial.print("Temperature = "); Serial.println(temperature);
  Serial.print("Analog In = "); Serial.println(analogIn);

  if (temperature > 32){
    digitalWrite(ledPin, HIGH);   // set the LED on
  }
  else{
    digitalWrite(ledPin, LOW);  
  }

  // Check and print any faults
  uint8_t fault = thermo.readFault();
  if (fault) {
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
    thermo.clearFault();
  }
 
  delay(2);
}
