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



RF24 radio(7, 8); // CE, CSN Teensy 3.5 Motoren-Board
RF24Network network(radio);
const uint16_t this_node = 02;   // Address of this node in Octal format ( 04,031, etc) // Motoreinheiten

const uint16_t master00 = 00;    // Address of the other node in Octal format // Motoreinheiten
const uint16_t node02 = 02; // Gedankenlesegerät
const uint16_t node03 = 03; // Maschinenkopf

const unsigned long interval_nrf_send_led = 950;  //ms  // How often to send data to the other unit
unsigned long last_sent_led;            // When did we last send?

const unsigned long interval_nrf_send_hub = 950;  //ms  // How often to send data to the other unit
unsigned long last_sent_hub;            // When did we last send?


// Datenkonstrukt eingehend Gedankenlesegerät
struct dataStruct2
{
  byte function;
  byte value1;
  byte value2;
  byte value3;
  byte value4;
} myIncomingPacketGedankenlesegeraet;



struct dataStruct { // Datenkonstrukt Ausgehend
  byte function; // 1 = Gedankenpacket
  byte value1; // Signalstärke
  byte value2; // Meditation
  byte value3; // Batterie
  byte value4; // LED Programm
} myOutgoingPacketMotoreinheiten;

/*
  struct dataStruct2 { // Datenkonstrukt eingehend Gedankenpacket
  byte function;
  byte value1;
  byte value2;
  byte value3;
  } myOutgoingPacketLed;
*/

// Datenkonstrukt ausgehend Maschinenkopf Hub und LED
struct dataStruct3
{
  byte function;
  byte value1;
  byte value2;
} myOutgoingPacketMaschinenkopf;


// Datenkonstrukt eingehend Maschinenkopf Konrtolle
struct dataStruct4
{
  byte function; // 10 = erfolgreich.
  byte value1;  // 1 = erfolgreich, 0 = nicht erfolgreich.
} myIncomingPacketMaschinenkopf;



void setup()
{
  SPI.setSCK(14);
  SPI.begin();

  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15, 15);
  // delay How long to wait between each retry, in multiples of 250us, max is 15. 0 means 250us, 15 means 4000us.
  //count How many retries before giving up, max 15
}


void loop()
{

  //network.update();


  myOutgoingPacketMotoreinheiten.function = 1;
  myOutgoingPacketMotoreinheiten.value1 = 0;
  myOutgoingPacketMotoreinheiten.value2 = 88;
  myOutgoingPacketMotoreinheiten.value3 = 55; // Batteriestatus -> Batterie leer;
  RF24NetworkHeader header(master00);   // (Address where the data is going)
  bool ok = network.write(header, &myOutgoingPacketMotoreinheiten, sizeof(myOutgoingPacketMotoreinheiten)); // Send the data



  /*

    //===== Receiving =====//
    while (network.available())
    { // Is there any incoming data?
    RF24NetworkHeader header;
    network.read(header, &myIncomingPacketGedankenlesegeraet, sizeof(myIncomingPacketGedankenlesegeraet)); // Read the incoming data

    // GEDANKENLESEGERÄT
    if (header.from_node == 2)
    {
    }

    }
  */
}
