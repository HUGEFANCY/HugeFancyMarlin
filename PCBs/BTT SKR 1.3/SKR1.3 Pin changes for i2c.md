
https://github.com/MarlinFirmware/Marlin/issues/15754#issuecomment-552363829

**possible pins for i2c on btt skr 1.3 :**

P0.0 SDA1 is used for E1DIR
P0.1 SCL1 is used for E1STP
P0.10 SDA2 is used for E1EN
P0.11 SCL2 is used for E0DIR
P0.19 SDA1 is used for YSTP
P0.20 SCL1 is used for YDIR
P0.27 SDA0 is used for SD card Data
P0.28 SCL0 is used on pin 9 of EXP1 (ie LCD connector)

**Plan:**

put E1STP and E1DIR on E1 UART pins (P1.4 + P1.1)
use P0.0 and P0.1 for i2c 

changes made in : 
- Marlin/src/pins/lpc1768/pins_BTT_SKR_common.h
- Marlin/src/pins/lpc1768/pins_BTT_SKR_V1_3.h

i2c pin variable names taken from:
- Marlin/src/pins/sanguino/pins_OMCA.h (line 142)