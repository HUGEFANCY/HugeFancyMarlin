/**
    Modbus slave example 1:
    The purpose of this example is to link a data array
    from the Arduino to an external device.

    Recommended Modbus Master: QModbus
    http://qmodbus.sourceforge.net/
*/

#include <ModbusRtu.h>

// assign the Arduino pin that must be connected to RE-DE RS485 transceiver
#define TXEN  13


// data array for modbus network sharing
uint16_t au16data[16] =
{
  3, 1415, 9265, 4, 2, 7182, 28182, 8, 0, 0, 0, 0, 0, 0, 1, 65535
};

/**
    Modbus object declaration
    u8id : node id = 0 for master, = 1..247 for slave
    u8serno : serial port (use 0 for Serial)
    u8txenpin : 0 for RS-232 and USB-FTDI
                 or any pin number > 1 for RS-485
*/
Modbus slave(1, Serial1, TXEN); // this is slave @1 and RS-232 or USB-FTDI

int8_t state = 0; // Status über die abgeschlossenene Übertragung

void setup() 
{
  Serial.begin(9600);
  delay(100);
  slave.begin( 19200 ); // baud-rate at 19200
}

void loop()
{


  // [0] -> INPUTS
  bitWrite( au16data[0], 0, 22); // Speichere 22 auf 0
  bitWrite( au16data[0], 1, 44); // Speichere 22 auf 1
  bitWrite( au16data[0], 2, 55);
  bitWrite( au16data[0], 3, 66);

  // [1] -> LESEN WAS ANKAM
  byte ankunft_0 = bitRead( au16data[1], 0 );
  byte ankunft_1 = bitRead( au16data[1], 1 );



  slave.poll( au16data, 16 );


  // DIAGNOSE
  state = slave.poll( au16data, 9 ); //Serial.println(state);
  // 0 = keine Datenanforderung, 1-4 = Fehler, >4 Bestellung erfolgreich verarbeitet

  // diagnose communication and sent to master
  au16data[6] = slave.getInCnt();  //Serial.println(slave.getInCnt());
  au16data[7] = slave.getOutCnt();  //Serial.println(slave.getOutCnt());
  au16data[8] = slave.getErrCnt(); //Serial.println(slave.getErrCnt());


}
