#define DEBUG //uncomment if final

#include <ModbusSlave.h>

/* slave id = 101, rs485 control-pin = 2, baud = 9600
*/
#define SLAVE_ID 1
#define CTRL_PIN 13
#define BAUDRATE 9600


uint16_t memory_slave1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t memory_slave1_size = sizeof(memory_slave1) / sizeof(memory_slave1[0]); // Get the size of the input_pins array

Modbus slave(Serial1, SLAVE_ID, CTRL_PIN);

void setup()
{
  //slave.cbVector[CB_WRITE_HOLDING_REGISTERS] = writeDigitlOut;
  Serial.begin( BAUDRATE );
  Serial1.begin( BAUDRATE );
  slave.begin( BAUDRATE );
  delay(1000);
  Serial.print("Slave Start");
}

int incomingByte = 0; // Für eingehende serielle Daten


void loop()
{
  slave.poll();


  if (Serial1.available() > 0) 
  {
    // Lies das eingehende Byte:
    incomingByte = Serial1.read();

    // Ausgeben:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  //readMemorySlave1(03,1,1);
  
}


// Handle the function codes Write Holding Register(s) (FC=06, FC=16)
uint8_t writeMemorySlave1(uint8_t fc, uint16_t address, uint16_t length)
{
    // Check if the requested addresses exist in the array
    if (address > memory_slave1_size || (address + length) > memory_slave1_size)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    Serial.println(F("Writing memory on Slave 1"));

    // Write the received data into the memory array.
    for (uint8_t i = 0; i < length; ++i)
    {
        memory_slave1[address + i] = slave.readRegisterFromBuffer(i);
    }
    return STATUS_OK;
}

// Handle the function code Read Holding Registers (FC=03).
uint8_t readMemorySlave1(uint8_t fc, uint16_t address, uint16_t length)
{
    // Check if the requested addresses exist in the array.
    if (address > memory_slave1_size || (address + length) > memory_slave1_size)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    Serial.println(F("Reading memory from Slave 1"));

    // Write the memory array into the send buffer.
    for (uint8_t i = 0; i < length; ++i)
    {
        slave.writeRegisterToBuffer(i, memory_slave1[address + i]);
    }
    return STATUS_OK;
}
