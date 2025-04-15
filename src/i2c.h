////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once

#include <stdint.h>
#include <hardware/i2c.h>
#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(i2c_default)
  #warning "// i2c not enabled //"
#endif

// #ifndef I2C_BUS_DEFINES
// #define I2C_BUS_DEFINES
constexpr bool I2C_HOLD_BUS    = true;
constexpr bool I2C_RELEASE_BUS = false;
// #endif

constexpr uint32_t I2C_100KHZ = 100 * 1000UL;
constexpr uint32_t I2C_400KHZ = 400 * 1000UL;
constexpr uint32_t I2C_1000KHZ = 1000 * 1000UL;
constexpr uint32_t I2C_1700KHZ = 1700 * 1000UL;
constexpr uint32_t I2C_3400KHZ = 3400 * 1000UL;


enum i2c_errors {
  INVALID_SCL_PIN= -1,
  INVALID_SDA_PIN= -2,
  INVALID_I2C_PORT = -3,
  I2C_PTR_NULL = -4
};

typedef struct {
  i2c_inst_t *i2c;
  uint8_t addr;     // sensor address
  // const uint32_t baud;
  // const uint32_t pin_sda;
  // const uint32_t pin_scl;
} gci_i2c_t;

// int32_t gci_i2c_init(gci_i2c_t *hw, uint32_t port, uint8_t addr, 
//   uint32_t baud, pin_t sda, pin_t scl);
int32_t gci_i2c_init(uint32_t port, uint32_t baud, pin_t sda, pin_t scl);
int32_t gci_i2c_read(const gci_i2c_t *hw, uint8_t reg, uint8_t *dst, uint32_t size);
int32_t gci_i2c_write(const gci_i2c_t *hw, uint8_t reg, uint8_t *src, uint32_t size);

#ifdef __cplusplus
}
#endif