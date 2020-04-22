/*

  Basic.pde - example using ModbusMaster library

  Library:: ModbusMaster
  Author:: Doc Walker <4-20ma@wvfans.net>

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

#include <ModbusMaster.h>

#define MAX485_DE      13

// instantiate ModbusMaster object
ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_DE, 0);
}

void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_DE, 0);

  // communicate with Modbus slave ID 5 over Serial (port 0)
  node.begin(5, Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  delay(1000);
  Serial.println("Master Start");
}


void loop()
{
  
  static uint32_t i;
  uint8_t j, result;
  uint16_t data[6];

  //Serial.println("writeSingleRegister");
  //result = node.writeSingleRegister(3, 22);

  // set word 0 of TX buffer to least-significant word of counter (bits 15..0)
  node.setTransmitBuffer(0, lowWord(i));

  // set word 1 of TX buffer to most-significant word of counter (bits 31..16)
  node.setTransmitBuffer(1, highWord(i));

  // write TX buffer to (2) 16-bit registers starting at NANO_REG(4)
  //result = node.writeMultipleRegisters(4, 2222);
  Serial.println(result);


  // set word 0 of TX buffer to least-significant word of counter (bits 15..0)
  //node.setTransmitBuffer(0, 33);

  // set word 1 of TX buffer to most-significant word of counter (bits 31..16)
  //node.setTransmitBuffer(1, 44);

  // slave: write TX buffer to (2) 16-bit registers starting at register 0
  //result = node.writeMultipleRegisters(0, 2);



  // slave: read (6) 16-bit registers starting at register 2 to RX buffer
  result = node.readHoldingRegisters(2, 6);

    // do something with data if read is successful
    if (result == node.ku8MBSuccess)
    {
    for (j = 0; j < 6; j++)
    {
      data[j] = node.getResponseBuffer(j);
    }
    }
}
