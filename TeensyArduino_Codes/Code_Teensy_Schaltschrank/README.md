
These are the codes running on the Teenssy located in the switch cabinet 

This teensy talks to the Marlin Board (BTT SKR 1.3) via I2c and sends the info further to the Teensy on the Z-Axis via RS485. 
There is also a watchdog that can kill the Marlin Board if necessary. 

## Code_Teensy_Schaltschrank.ino
- Base code and loop that is running
- imports all the other .ino files for execution. 

## I2C_to_Marlin.ino
- communicates with Marlin on the SKR Board:
    - sends current Hotend Temperature when requested
    - Receives Hotend Target Temperature for forwarding to the Hotend

## Motoren_Raeder.ino
- Future Feature to make the entire Printer Mobile

## RS485.ino 
- Communication between the two teensies, sends header, content and checksum every 1 second

## Relays.ino
- Starting and stopping the relay for the air compressor.   

## RGB_Led.ino
- RGB LED as visual status signal 

