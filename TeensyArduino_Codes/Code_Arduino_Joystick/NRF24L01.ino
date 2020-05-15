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

RF24 radio(5, 6); // CE, CSN -> Arduino Pro Mini Board 5, 6
RF24Network network(radio);

const int FunkChannel = 90;
const uint16_t FunkMasterSchaltschrank = 00; // Address of the other node in Octal format // Schaltschrank, Master
const uint16_t FunkSlaveJoystick = 01; // Joystick, Slave

Metro Metro_FunkCheck = Metro(50);


struct DataPackageIncomming // Max size of this struct is 32 bytes - NRF24L01 buffer limit
{
  byte TargetTempZone1 = 0;
  byte TargetTempZone2 = 0;
};
DataPackageIncomming dataIncoming; // Create a variable with the above structure



void setup_Funk()
{
  SPI.begin();
  radio.begin();
  network.begin(FunkChannel, FunkSlaveJoystick); //(channel, node address)
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15, 15);
  // delay How long to wait between each retry, in multiples of 250us, max is 15. 0 means 250us, 15 means 4000us.
  //count How many retries before giving up, max 15
}

void FunkData()
{
  // Send data:
  RF24NetworkHeader header(FunkMasterSchaltschrank);   // Address where the data is going
  bool ok = network.write(header, &dataOutgoing, sizeof(dataOutgoing)); // Send the data
}


void loop_FunkCheck()
{
  //===== Receiving =====//
  network.update();

  while (network.available()) // Is there any incoming data?
  {
    RF24NetworkHeader header(FunkMasterSchaltschrank);
    network.read(header, &dataIncoming, sizeof(dataIncoming)); // Read the incoming data

    if (header.from_node == FunkMasterSchaltschrank)
    {
      Serial.println("--- Incomming Data --- ");
      Serial.print("TargetTempZone1 = "); Serial.println(dataIncoming.TargetTempZone1);
      Serial.print("TargetTempZone2 = "); Serial.println(dataIncoming.TargetTempZone2);
      Serial.println();
    }
  }
}
