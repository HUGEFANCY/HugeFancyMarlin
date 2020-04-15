/*
This NanoJ Example Code is based on our experience with typical user requirements in a wide range
of industrial applications and is provided without guarantee regarding correctness and completeness.
It serves as general guidance and should not be construed as a commitment of Nanotec to guarantee its
applicability to the customer application without additional tests under the specific conditions
and – if and when necessary – modifications by the customer. 

The responsibility for the applicability and use of the NanoJ Example Code in a particular
customer application lies solely within the authority of the customer.
It is the customer's responsibility to evaluate, investigate and decide,
whether the Example Code is valid and suitable for the respective customer application, or not.
Defects resulting from the improper handling of devices and modules are excluded from the warranty.
Under no circumstances will Nanotec be liable for any direct, indirect, incidental or consequential damages
arising in connection with the Example Code provided. In addition, the regulations regarding the
liability from our Terms and Conditions of Sale and Delivery shall apply.
*/

//This example shows how to use the nanotec.h
//In this example the motor is started in profile velocity mode
//Digital Input 1 starts/stopps the motor 
//Digital Inputs 2-4 select the velocity for the motor
//Digital Output 1 is set or cleared depending on whether the motor is in the state Operation Enabled

map U16 Controlword as inout 0x6040:00
map U16 Statusword as input 0x6041:00
map U32 Inputs as input 0x60FD:00
map U32 Outputs as inout 0x60FE:01
map S08 ModesOfOperation as output 0x6060:00
map S08 ModesOfOperationDisplay as input 0x6061:00
map S16 AnalogInput as input 0x3220:01
map S32 TargetVelocity as output 0x60FF:00
//TargetVelocity is not part of the mappings needed in nanotec.h

#include "wrapper.h"
#include "nanotec.h"

void user()
{
	ModesOfOperation(3);	//set the Mode to Profile Velocity 
	SwitchOn();				//change the state to Switched On
	SetDigitalOutput(1);	//set Digital Output 1				
	
	while(true)
	{
		
		if(!DigitalInput(2) & !DigitalInput(3) & !DigitalInput(4))		//if Inputs 2, 3 and 4 are inactive...
		{
			Halt(true);													//Velocity is forced to 0 by activating Halt
		}
		else if(DigitalInput(2) & !DigitalInput(3) & !DigitalInput(4))	//else if Input 2 is active, 3 and 4 are inactive...
		{
			Halt(false);												//deactivate Halt
			Out.TargetVelocity = 100;									//Velocity = 100
		}
		else if(!DigitalInput(2) & DigitalInput(3) & !DigitalInput(4))	//else if Input 3 is active, 2 and 4 are inactive...
		{
			Halt(false);												//deactivate Halt
			Out.TargetVelocity = 200;									//Velocity = 200
		}
		else if(DigitalInput(2) & DigitalInput(3) & !DigitalInput(4))	//else if Inputs 2 and 3 are active, 4 is inactive...
		{
			Halt(false);												//deactivate Halt
			Out.TargetVelocity = 300;									//Velocity = 300
		}
		else if(!DigitalInput(2) & !DigitalInput(3) & DigitalInput(4))	//else if Input 4 is active, 2 and 3 are inactive...
		{
			Halt(false);												//deactivate Halt
			Out.TargetVelocity = AnalogInput();							//Velocity = Value of Analog Input (0-1023)
		}		
			
		if(DigitalInput(1))												//if Input 1 is active 
		{
			EnableOperation();											//change the state to Operation Enabled
			ClearDigitalOutput(1);										//clear Digital Output 1
		}
		else															//else (Input 1 is inactive)
		{
			SwitchOn();													//change the state to Switched On
			SetDigitalOutput(1);										//set Digital Output 1
			
		}		
		yield();
	}
}