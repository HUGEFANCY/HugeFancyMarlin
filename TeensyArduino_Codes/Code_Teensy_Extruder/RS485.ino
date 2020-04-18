
// RS485 long distance communication betweent Teensy Schaltschrank (Master) and Teensy Extruder (Slave)
// Anleitung: https://circuitdigest.com/microcontroller-projects/rs485-serial-communication-between-arduino-uno-and-arduino-nano

// Slave Device

// PINOUT
// R0 -> Teensy Rx1 / PIN 0
// RE = DE -> Teensy PIN 8
// DI -> Teensy Tx1 / PIN 1
// VCC -> 5V
// A -> Kabelterminal 17
// B -> Kabelterminal 18
// GND -> Teensy GND

const byte RS485_enablePin = 8;

const uint8_t header = 0x7E; // Bufferheader: Verkündung Teensy Schaltschrank
const uint8_t bufferSize = 5;
uint8_t buffer[bufferSize];
// Byte 0 Header (0x7E)
// Byte 1 targetTempExtruderMarlin
// Byte 2 ExtruderCoolingStatusMarlin
// Byte 3 pwmValuePartCoolingFanMarlin
// Byte 4 Checksum
uint8_t readCounter;
uint8_t isHeader;
uint8_t firstTimeHeader; // Flag that helps us restart counter when we first find header byte

void RS485_setup()
{
  while (!Serial1);
  Serial1.begin(9600); // Serial1 für RS485

  readCounter = 0;
  isHeader = 0;
  firstTimeHeader = 0;

  pinMode(RS485_enablePin, OUTPUT);
  delay(10);
  digitalWrite(RS485_enablePin, LOW);  // always LOW to receive value from Master
}

void RS485_updateVariables()
{
  if (Serial1.available() > 0) // Check if there is any data available to read
  {
    uint8_t c = Serial.read(); // read only one byte at a time

    if (c == header) // Check if header is found
    {
      // We must consider that we may sometimes receive unformatted data, and given the case we must ignore it and restart our reading code.
      // If it's the first time we find the header, we restart readCounter indicating that data is coming.
      // It's possible the header appears again as a data byte. That's why this conditional is implemented, so that we don't restart readCounter and corrupt the data.
      if (!firstTimeHeader)
      {
        isHeader = 1;
        readCounter = 0;
        firstTimeHeader = 1;
      }

      buffer[readCounter] = c; // store received byte, increase readCounter
      readCounter++;

      if (readCounter >= bufferSize) // prior overflow, we have to restart readCounter
      {
        readCounter = 0;

        if (isHeader) // if header was found
        {

          uint8_t checksumValue = buffer[4]; // get checksum value from buffer's last value, according to defined protocol
          if (verifyChecksum(checksumValue)) // perform checksum validation, it's optional but really suggested
          {
            // erhaltene Daten updaten
            targetTempExtruderMarlin = map(buffer[1],0,255,0,511); // gesendete 8 Bit Wert wiedeer auf die ursprünglichen 9 Bit zurückführen
            targetExtruderCoolingStatusMarlin = buffer[2];
            targetPwmValuePartCoolingFanMarlin = buffer[3];
          }

          // restart header flag
          isHeader = 0;
          firstTimeHeader = 0;
        }
      }
    }
  }
}


// This a common checksum validation method. We perform a sum of all bytes, except the one that corresponds to the original checksum value. After summing we need to AND the result to a byte value.
uint8_t verifyChecksum(uint8_t originalResult) 
{
  uint8_t result = 0;
  uint16_t sum = 0;

  for (uint8_t i = 0; i < (bufferSize - 1); i++) 
  {
    sum += buffer[i];
  }
  result = sum & 0xFF;

  if (originalResult == result) 
  {
    return 1;
  } else 
  {
    return 0;
  }
}
