// RS485 long distance communication betweent Teensy Schaltschrank (Master) and Teensy Extruder (Slave)
// Anleitung: https://circuitdigest.com/microcontroller-projects/rs485-serial-communication-between-arduino-uno-and-arduino-nano

// Master Devive 

// PINOUT 
// R0 -> Teensy Rx1 / PIN 0
// RE = DE -> Teensy PIN 8
// DI -> Teensy Tx1 / PIN 1
// VCC -> 5V
// A -> Kabelterminal 17
// B -> Kabelterminal 18
// GND -> Teensy GND

const byte RS485_enablePin = 8;  

void RS485_setup()
{
  Serial1.begin(9600); // Serial1 für RS485
    
  pinMode(RS485_enablePin, OUTPUT);
  delay(10);
  digitalWrite(RS485_enablePin, HIGH);  // always high as Master Writes data to Slave
}

void RS485_sentSignal(int signalToSent)
{
   Serial1.println(signalToSent); 
}
