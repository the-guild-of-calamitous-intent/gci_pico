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

typedef struct {
  i2c_inst_t *i2c;
  uint8_t addr;     // sensor address
  // uint32_t baudrate;
  // const uint32_t baud;
  // const uint32_t pin_sda;
  // const uint32_t pin_scl;
} gci_i2c_t;

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
  I2C_PTR_NULL = -4,
  I2C_UNINITIALIZED = -99
};

gci_i2c_t* gci_i2c0_init(uint8_t addr);

// gci_i2c_t* gci_i2c0_bus_init(uint32_t baud, pin_t pin_sda, pin_t pin_scl);
int32_t gci_i2c0_bus_init(uint32_t baud, pin_t pin_sda, pin_t pin_scl);
int32_t gci_i2c1_bus_init(uint32_t baud, pin_t pin_sda, pin_t pin_scl);

int32_t gci_i2c_read(i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint8_t *dst, uint32_t size);
int32_t gci_i2c_write(i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint8_t *src, uint32_t size);
uint32_t gci_i2c_available(i2c_inst_t *i2c);
uint32_t gci_i2c0_available();
uint32_t gci_i2c1_available();


// gci_i2c_t* gci_i2c1_init_t(uint8_t addr);
// int32_t gci_i2c_init(gci_i2c_t *hw, uint32_t port, uint8_t addr, 
//   uint32_t baud, pin_t sda, pin_t scl);
// int32_t gci_i2c_init(uint32_t port, uint32_t baud, pin_t sda, pin_t scl);


// gci_i2c_t* gci_i2c0_init_t(uint8_t addr);
// int32_t gci_i2c0_read(uint8_t addr, uint8_t reg, uint8_t *dst, uint32_t size);
// int32_t gci_i2c0_write(uint8_t addr, uint8_t reg, uint8_t *src, uint32_t size);
// int32_t gci_i2c1_read(uint8_t addr, uint8_t reg, uint8_t *dst, uint32_t size);
// int32_t gci_i2c1_write(uint8_t addr, uint8_t reg, uint8_t *src, uint32_t size);
// int32_t gci_i2c_read(const gci_i2c_t *hw, uint8_t reg, uint8_t *dst, uint32_t size);
// int32_t gci_i2c_write(const gci_i2c_t *hw, uint8_t reg, uint8_t *src, uint32_t size);

#ifdef __cplusplus
}
#endif