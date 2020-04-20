// PID Temperaturreglung Extruder

// Extruder
int TempExtruderObenrum = 0; // max 9 Bit = 511°C
int TempExtruderUntenrum = 0; // max 9 Bit = 511°C
bool LuefterObenrum = false;
bool LuefterObenUntenrum = false;

// Wasserkühlung
int TempWatercoolingCold = 0; // max 9 Bit = 511°C
int TempWatercoolingWarm = 0; // max 9 Bit = 511°C
