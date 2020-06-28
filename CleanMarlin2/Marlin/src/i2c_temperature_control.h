#pragma once
#include "../src/core/macros.h"

#include "../src/feature/twibus.h"

//#define TWIBUS_BUFFER_SIZE 32

/**
 * I2C_TempControl class
 *
 *
 */
class I2C_TempControl {

  public:
  /**
     * @brief Send hotend target temp via i2c
     * @details Sends hotend target temperature via i2c, including header and checksum , returns true if successful 
     *
     * @param target_hotend index of the target hotend
     * @param target_temperature target temperature to send 
     * @return 0 or 1 
     */
    uint8_t send_target_temp(uint8_t target_hotend, uint16_t target_temperature);

  /**
     * @brief Request current Hotend temperature from i2c-slave 
     * @details request Hotend temp by requesting n bytes from i2c slave.  
     *
     * @param target_hotend index of the target hotend 
     * @return hotend temperature 
     */
    uint8_t request_hotend_temp(uint8_t target_hotend);


};

