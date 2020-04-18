// RS485 long distance communication betweent Teensy Schaltschrank (Master) and Teensy Extruder (Slave) über UART with selfmade Communication Protocol
// Anleitung RS485 UART: https://circuitdigest.com/microcontroller-projects/rs485-serial-communication-between-arduino-uno-and-arduino-nano
// Anleitung designing a communication protocol: https://henryforceblog.wordpress.com/2015/03/12/designing-a-communication-protocol-using-arduinos-serial-library/

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

const uint8_t header_updateVariables = 0x7E; // Bufferheader: Verkündung Teensy Schaltschrank
unsigned long RS485_header_updateVariables_updatePreviousMillis = 0;

const uint8_t header_Farbmischer = 0x7D; // Bufferheader: Aktion Farbmischer

const uint8_t bufferSize = 5;
uint8_t buffer[bufferSize];

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

void RS485_Test()
{
  while (Serial1.available())
  {
    int empfangen = Serial1.parseInt();
    TM1637_test(empfangen);
    Serial.println(empfangen);
  }
}

void RS485_CheckIfUpdateAvalible()
{
  if (Serial1.available() > 0) // Check if there is any data available to read
  {
    uint8_t c = Serial1.read(); // read only one byte at a time

    if ((c == header_updateVariables) or (c == header_Farbmischer)) // Check if header is found
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
          // Folgende Daten wurden erhalten:

          // header Update globale Variablen
          if (buffer[0] == header_updateVariables)
          {
            // Byte 0 Header (0x7E)
            // Byte 1 targetTempExtruderMarlin Byte 01
            // Byte 2 targetTempExtruderMarlin Byte 02
            // Byte 3 pwmValuePartCoolingFanMarlin
            // Byte 4 Checksum

            // Update globale Variablen
            targetTempExtruderMarlin = buffer[1] + buffer[2]; // gesendete 8 Bit Werte wiedeer auf die ursprünglichen 9 Bit zurückführen
            PwmValuePartCoolingFanMarlin = buffer[3];
            RS485_header_updateVariables_updatePreviousMillis = 0; // für Timeout falls wir lange nichts mehr vom Teensy Schaltschrank gehört haben
          }

          // header Farbmischer
          if (buffer[0] == header_Farbmischer)
          {
            // Byte 0 Header (0x7D)
            // Byte 1 Schaufeln Links 
            // Byte 2 Schaufeln Rechts
            // Byte 3 frei
            // Byte 4 Checksum

            byte Schaufeln_L = buffer[1];
            byte Schaufeln_R = buffer[2];
            Farbmischer_GibFarbe(Schaufeln_L, Schaufeln_R); // Motoren Farbmischer starten
          }
        }
        // restart header flag
        isHeader = 0;
        firstTimeHeader = 0;
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
