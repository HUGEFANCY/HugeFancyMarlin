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

// in this example the operationmode will be set to clock direction mode and enabled with an input

//1. Step: mapping the frequently used SDO´s
map U16 ControlWord as output 0x6040:00
map U32 Inputs as input 0x60FD:00

#include "wrapper.h"

//2. Step: call Main function and make nevessary settings

void user()
{
	bool bEnabled = false;  			// bool variable with name "bEnabled"
	
	od_write(0x6060, 0x00, 0xff);		// set the mode of operation to clock-direction mode (0xff = -1)
	
//3. Step: switch on the state machine, use enable input

	Out.ControlWord = 0x6;				// switch to the "enable voltage" state
	do 	{
		yield();						// waiting for the next cycle (1ms)
		}
		while ( (od_read(0x6041, 0x00) & 0xEF) != 0x21);   // wait until drive is in state "enable voltage"
	

	// checking the statusword (0x6041) for the bitmask: xxxx xxxx x01x 0001
	
	
	while(true)
	{
		if((In.Inputs & 0x80000) != 0)  // checking input 4 for not low
		{	
			if (bEnabled == false)		// motor is not running
			{
				bEnabled = true;		// then start the motor with...
				Out.ControlWord = 0x7;	// switch to the "switched on" state
				do 	{
						yield();						// waiting for the next cycle (1ms)
					}
					while ( (od_read(0x6041, 0x00) & 0xEF) != 0x23);   // wait until drive is in state "switched on"	
					// checking the statusword (0x6041) for the bitmask: xxxx xxxx x01x 0011				
				Out.ControlWord = 0xF;	// switch to the "enable operation" state and starts the velocity mode
				do 	{
						yield();						// waiting for the next cycle (1ms)
					}
					while ( (od_read(0x6041, 0x00) & 0xEF) != 0x27);   // wait until drive is in state "operation enabled"	
					// checking the statusword (0x6041) for the bitmask: xxxx xxxx x01x 0111	
			}
		}
		else                			// if input 1 is low
		{	
			if (bEnabled == true)		// motor is started
			{
				bEnabled = false;		// then stop the motor with...
				Out.ControlWord = 0x6;	// switch to the "enable voltage" state 
				do 	{
						yield();						// waiting for the next cycle (1ms)
					}
					while ( (od_read(0x6041, 0x00) & 0xEF) != 0x21);   // wait until drive is in state "enable voltage"
	
					// checking the statusword (0x6041) for the bitmask: xxxx xxxx x01x 0001
			}
		}

		yield();						// waiting for the next cycle (1ms)
	} 
}	