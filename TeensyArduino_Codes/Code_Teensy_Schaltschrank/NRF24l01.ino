/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
          == Base/ Master Node 00==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/


#include <SPI.h>

#include <RF24Network.h>
#include "RF24.h"

RF24 radio(7, 8); // CE, CSN -> Teensy Board 7, 8 // SPI Channel 0 (ABER modefiziert): MOSI:11, MISO:12, SCK:14
RF24Network network(radio);

const int FunkChannel = 90;
const uint16_t FunkMasterSchaltschrank = 00; // Address of the other node in Octal format // Schaltschrank, Master
const uint16_t FunkSlaveJoystick = 01; // Joystick, Slave

// Datenkonstrukt Eingehend

struct DataPackageIncoming // Max size of this struct is 32 bytes - NRF24L01 buffer limit
{
  byte header = 0; // 1 = Temp                      // 2 = Joystick
  byte val1 = 0;   // NewTargetTemp_Zone1           // j1PotX;
  byte val2 = 0;   // NewTargetTemp_Zone2           // j1PotY;
  byte val3 = 0;   // PwmValuePartCoolingFanMarlin  // j1Button;
  byte val4 = 0; // j2PotX;
  byte val5 = 0; // j2PotY;
  byte val6 = 0; // j2Button;
  byte val7 = 0; // pot1;
  byte val8 = 0; // pot2;
  byte val9 = 0; // tSwitch1;
  byte val10 = 0; // tSwitch2;
  byte val11 = 0; // button1;
  byte val12 = 0; // button2;
  byte val13 = 0; // button3;
  byte val14 = 0; // button4;
};
DataPackageIncoming dataIncoming; // Create a variable with the above structure

struct DataPackageOutgoing // Max size of this struct is 32 bytes - NRF24L01 buffer limit
{
  byte header = 0;
  byte val1 = 0; // TargetTemperatureZone_1 (laut Teensy Schatschrank)
  byte val2 = 0; // TargetTemperatureZone_2 (laut Teensy Schatschrank)
  byte val3 = 0; // RealTemperatureZone_1
  byte val4 = 0; // RealTemperatureZone_2
};
DataPackageOutgoing dataOutgoing; // Create a variable with the above structure


void setup_Funk()
{
  SPI.setSCK(14); // changes SCK Pin Teensy
  SPI.begin();
  radio.begin();
  network.begin(FunkChannel, FunkMasterSchaltschrank); //(channel, node address)
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15, 15);
  // delay How long to wait between each retry, in multiples of 250us, max is 15. 0 means 250us, 15 means 4000us.
  //count How many retries before giving up, max 15
}


void loop_FunkCheck()
{
  //===== Receiving =====//
  network.update();

  while (network.available()) // Is there any incoming data?
  {
    RF24NetworkHeader header(FunkSlaveJoystick);
    network.read(header, &dataIncoming, sizeof(dataIncoming)); // Read the incoming data

    if ((header.from_node == FunkSlaveJoystick) and (dataIncoming.header == 1))
    {
      TargetTemperatureZone_1 = dataIncoming.val1;
      TargetTemperatureZone_2 = dataIncoming.val2;
      PwmValuePartCoolingFanMarlin = dataIncoming.val3;
      Serial.println("Funk funktet new target Temps");
      Serial.println(TargetTemperatureZone_1);
      Serial.println(TargetTemperatureZone_2);
      Serial.print("PWM Cooling = ");Serial.println(PwmValuePartCoolingFanMarlin);
    }
  }
  FunkData_Temp(); // Anschließend senden wir mal was
}

void FunkData_Temp()
{
  // Send data:
  RF24NetworkHeader header(FunkSlaveJoystick);   // Address where the data is going
  dataOutgoing.header = 1; // Temp
  dataOutgoing.val1 = TargetTemperatureZone_1;
  dataOutgoing.val2 = TargetTemperatureZone_2;
  dataOutgoing.val3 = RealTemperatureZone_1;
  dataOutgoing.val4 = RealTemperatureZone_2;

  bool ok = network.write(header, &dataOutgoing, sizeof(dataOutgoing)); // Send the data
}
