
These are the codes running on the Teensy that is located next to the Extruder-unit on the Z- axis:

## Code_Teensy_Extruder.ino
- Main code running on the teensy, imports funcitons from the files below

## Gameover.ino
- safety watchdog 
## I2C_Master.ino
- ? 

## PID_TemperatureControl
- controls the hotend temperature via PID 

## Motoren.ino
- ?

## Probe.ino
- BedLeveling Probe 

## PT100_MAX31865.ino
- Interfaces with MAX31865 boards and thermocouples

## Relays.ino
- Control of relays for heater and light 

## RGB_Led.ino
- RGB-LED as a visual status indication located on the PCB

## RS485.ino
- Communication with the teensy located in the switch cabinet

## Tastertureingabe.ino
- ?

## TempWasser.ino
- control of water cooling temps 

## TM1637.ino
- 7 Segment displays located at the hotend 
    - these displays show hotend zone temps , water temps and other info 