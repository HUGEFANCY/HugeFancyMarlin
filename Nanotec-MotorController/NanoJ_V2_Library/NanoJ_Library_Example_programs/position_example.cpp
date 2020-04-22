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
//In this example the motor is started in profile position mode
//Digital Input 1 activates a new target position
//Digital Input 2 selects if a new target position should be relative or absolute
//Digital Input 3 selects if a new target position should be changed immediately or after the last target position was reached
//Digital Input 4 switches between two speeds (slow/fast)
//Digital Input 5 switches between two target positions (1000/4000)
//Digital Input 6 lets the motor perform a quick-stop
//Digital Output 1 is set or cleared depending on whether the last target has been reached

map U16 Controlword as inout 0x6040:00
map U16 Statusword as input 0x6041:00
map U32 Inputs as input 0x60FD:00
map U32 Outputs as inout 0x60FE:01
map S08 ModesOfOperation as output 0x6060:00
map S08 ModesOfOperationDisplay as input 0x6061:00
map S16 AnalogInput as input 0x3220:01
map S32 TargetPosition as output 0x607A:00
map U32	ProfileVelocity as output 0x6081:00
//TargetPosition and ProfileVelocity are not part of the mappings needed in nanotec.h

#include "wrapper.h"
#include "nanotec.h"

void user()
{
	ModesOfOperation(1);	//set the Mode to Profile Position 
	EnableOperation();		//change the state to Operation Enabled
	ClearDigitalOutput(1);	//clear Digital Output 1				
	
	while(true)
	{
		
		if(DigitalInput(2))												//if Input 2 is active...
		{
			RelativeMovement();											//set to relative movement
		}
		else															//else...
		{
			AbsoluteMovement();											//set to absolute movement
		}
		
		if(DigitalInput(3))												//if Input 3 is active...
		{
			ChangeSetPointImmediately(true);							//change setpoint immediately
		}
		else															//else...
		{
			ChangeSetPointImmediately(false);							//change setpoint after last target reached
		}
		
		if(DigitalInput(4))												//if Input 4 is active...
		{
			Out.ProfileVelocity=50;										//set velocity to 50 rpm
		}
		else															//else...
		{
			Out.ProfileVelocity=200;									//set velocity to 200 rpm
		}
		
		if(DigitalInput(5))												//if Input 5 is active...
		{
			Out.TargetPosition=1000;									//set target position to 1000
		}
		else															//else...
		{
			Out.TargetPosition=4000;									//set target position to 4000
		}
		
		if(DigitalInput(6))												//if Input 6 is active...
		{
			Quickstop();												//Quickstop
		}
		else															//else...
		{
			EnableOperation();											//change the state to Operation Enabled
		}
						
		if(DigitalInput(1))												//if Input 1 is active... 
		{
			NewSetPoint(true);											//set new setpoint
		}
		else															//else (Input 1 is inactive)
		{
			NewSetPoint(false);											//reset new setpoint		
		}	
		
		if(TargetReached())												//if the target position has been reached
		{
			SetDigitalOutput(1);										//set output 1
		}
		else															//else...														
		{
			ClearDigitalOutput(1);										//clear output 1
		}		
			
		yield();
	}
}