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
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
  byte pot1;
  byte pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;
};
DataPackageIncoming dataIncoming; // Create a variable with the above structure

struct DataPackageOutgoing // Max size of this struct is 32 bytes - NRF24L01 buffer limit
{
  byte TargetTempZone1 = 0;
  byte TargetTempZone2 = 0;
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

    if (header.from_node == FunkSlaveJoystick)
    {
      Serial.println("--- Incomming Data --- ");
      Serial.print("pot1 = "); Serial.println(dataIncoming.pot1);
      Serial.print("pot2 = "); Serial.println(dataIncoming.pot2);
      Serial.println();
    }
  }
}

void FunkData()
{
  // Send data:
  RF24NetworkHeader header(FunkSlaveJoystick);   // Address where the data is going
  bool ok = network.write(header, &dataOutgoing, sizeof(dataOutgoing)); // Send the data
}
