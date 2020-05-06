
These are the codes running on the Teenssy located in the switch cabinet 

This teensy talks to the Marlin Board (BTT SKR 1.3) via I2c and sends the info further to the Teensy on the Z-Axis via RS485. 
There is also a watchdog that can kill the Marlin Board if necessary. 

## Code_Teensy_Schaltschrank.ino
- Base code and loop that is running

## I2C_to_Marlin.ino
- communicates with Marlin:
    - sends current Hotend Temperature when requested
    - Receives Hotend Target Temperature for forwarding to the Hotend

## Motoren_Raeder.ino
- Future Code to make the entire Printer Mobile

## RS485.ino 
- Communication between the two teensies, sends header, content and checksum every 1 second