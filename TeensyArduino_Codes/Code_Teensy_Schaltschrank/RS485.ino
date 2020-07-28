// RS485 long distance communication betweent Teensy Schaltschrank (Master) and Teensy Extruder (Slave) über UART with selfmade Communication Protocol
// Tutorial RS485 UART: https://circuitdigest.com/microcontroller-projects/rs485-serial-communication-between-arduino-uno-and-arduino-nano
// Tutorial designing a communication protocol: https://henryforceblog.wordpress.com/2015/03/12/designing-a-communication-protocol-using-arduinos-serial-library/
// Modbus (not used) https://industruino.com/blog/our-news-1/post/modbus-rtu-master-and-slave-14

// Master Device

// PINOUT
// R0 -> Teensy Rx2
// RE = DE -> Teensy PIN 13
// DI -> Teensy Tx2
// VCC -> 5V
// A -> Kabelterminal 17
// B -> Kabelterminal 18
// GND -> Teensy GND

Metro sendeIntervall = Metro(100);

const byte RS485_enablePin = 13;

// Senden
const uint8_t bufferSize = 5;
uint8_t buffer[bufferSize];
// Empfangen
uint8_t readCounter = 0;
uint8_t isHeader = 0;
uint8_t firstTimeHeader = 0; // Flag that helps us restart counter when we first find header byte

// headers
const uint8_t header_AbsenderExtruder_Statusupdate = 0x7A;
const uint8_t header_AbsenderSchaltschrank_Statusupdate = 0x7B;
const uint8_t header_AbsenderSchaltschrank_FarbmischerAktion = 0x7C;

//const uint8_t header_AbsenderExtruder_Statusupdate = 0x7A; // Header
//const uint8_t header_AnswerUpdateVariables = 0x7C; // Bufferheader: Aktion Farbmischer

void RS485_setup()
{
  while (!Serial2); // Serial1 Teensy 3.2 defekt?
  Serial2.begin(115200); // Serial1 für RS485
  Serial2.transmitterEnable(RS485_enablePin);
  delay(10);
}


void RS485_Schaltschrank_CheckIfUpdateAvalible()
{
  //Serial.println("Checking for Update");
  int BreakCounter = 0;
  while (Serial2.available() > 0) // Check if there is any data available to read
  {
    uint8_t c = Serial2.read(); // read only one byte at a time

    if (c == header_AbsenderExtruder_Statusupdate) // Check if header is found
    {
      // We must consider that we may sometimes receive unformatted data, and given the case we must ignore it and restart our reading code.
      // If it's the first time we find the header, we restart readCounter indicating that data is coming.
      // It's possible the header appears again as a data byte.
      //That's why this conditional is implemented, so that we don't restart readCounter and corrupt the data.
      if (!firstTimeHeader)
      {
        isHeader = 1;
        readCounter = 0;
        firstTimeHeader = 1;
      }
    }
    buffer[readCounter] = c; // store received byte, increase readCounter ### FEHLER???
    readCounter++;

    if (readCounter >= bufferSize) // prior overflow, we have to restart readCounter
    {
      readCounter = 0;

      if (isHeader) // if header was found
      {

        uint8_t checksumValue = buffer[4]; // get checksum value from buffer's last value, according to defined protocol
        if (verifyChecksum(checksumValue)) // perform checksum validation, it's optional but really suggested
        {
          if (buffer[0] == header_AbsenderExtruder_Statusupdate)
          {
            Serial.println("Empfange Statusupdate Schaltschrank");
            // Byte 0 Header
            // Byte 1 RealTempExtruderForMarlin_01 Byte 01
            // Byte 2 RealTempExtruderForMarlin_02 Byte 02
            // Byte 3 Empty
            // Byte 4 Checksum

            RealTempExtruderForMarlin = buffer[1] + buffer[2]; // gesendete 8 Bit Werte wiedeer auf die ursprünglichen 9 Bit zurückführen
            Serial.print("RealTempExtruderForMarlin = "); Serial.println(RealTempExtruderForMarlin);
          }
        }
        // restart header flag
        isHeader = 0;
        firstTimeHeader = 0;
      }
    }
    
    BreakCounter++;
    if (BreakCounter >= 10)
    {
      Serial.println("Break Loop");
      break;
    }
  }

}

void loop_RS485_Schaltschrank_Send_Statusupdate()
{
  if (sendeIntervall.check() == 1)  // check if the metro has passed its interval
  {
    Serial.println("Sende Statusupdate Schaltschrank");

    // Byte 0 Header
    // Byte 1 TargetTempExtruderMarlin Byte 01
    // Byte 2 TargetTempExtruderMarlin Byte 02
    // Byte 3 pwmValuePartCoolingFanMarlin
    // Byte 4 Checksum

    buffer[0] = header_AbsenderSchaltschrank_Statusupdate;
    if (TargetTempExtruderMarlin <= 255)
    {
      buffer[1] = TargetTempExtruderMarlin; // Value between 0-255°C
      buffer[2] = 0;
    }
    else if ((TargetTempExtruderMarlin > 255) and (TargetTempExtruderMarlin <= 510))
    {
      buffer[1] = 255;
      buffer[2] = TargetTempExtruderMarlin - 255; // Value between 256-510°C
    }
    buffer[3] = PwmValuePartCoolingFanMarlin;
    buffer[4] = checksum();

    Serial2.write(buffer, bufferSize); // send all bytes stored in the buffer
  }
}



void RS485_Schaltschrank_Send_FarbmischerAktion(byte SchaufelnMotor_L, byte SchaufelnMotor_R)
{
  // Byte 0 Header (0x7D)
  // Byte 1 Schaufeln Links
  // Byte 2 Schaufeln Rechts
  // Byte 3 frei
  // Byte 4 Checksum

  buffer[0] = header_AbsenderSchaltschrank_FarbmischerAktion;
  buffer[1] = SchaufelnMotor_L;
  buffer[2] = SchaufelnMotor_R;
  buffer[3] = 0; // frei
  buffer[4] = checksum();

  Serial2.write(buffer, bufferSize); // We send all bytes stored in the buffer
}

//We perform a sum of all bytes, except the one that corresponds to the original checksum value. After summing we need to AND the result to a byte value.
uint8_t checksum()
{
  uint8_t result = 0;
  uint16_t sum = 0;

  for (uint8_t i = 0; i < (bufferSize - 1); i++) 
  {
    sum += buffer[i];
  }
  result = sum & 0xFF;

  return result;
}

// This a common checksum validation method.
// We perform a sum of all bytes, except the one that corresponds to the original checksum value.
// After summing we need to AND the result to a byte value.

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
