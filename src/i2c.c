////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#include "gci_pico/i2c.h"
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <stdint.h> // int types
#include <stdlib.h> // calloc
#include <string.h> // memcpy

typedef struct {
  uint8_t reg;
  uint8_t *buffer;
} __attribute__((packed)) i2c_msg_t;

typedef struct {
  uint32_t sda;
  uint32_t scl;
} valid_i2c_pins_t;

constexpr valid_i2c_pins_t i2c0_valid = {
    .sda = (1 << 0) | (1 << 4) | (1 << 8) | (1 << 12) | (1 << 16) | (1 << 20) | (1 << 24) | (1 << 28),
    .scl = (1 << 1) | (1 << 5) | (1 << 9) | (1 << 13) | (1 << 17) | (1 << 21) | (1 << 25) | (1 << 29)};

constexpr valid_i2c_pins_t i2c1_valid = {
    .sda = (1 << 2) | (1 << 6) | (1 << 10) | (1 << 14) | (1 << 18) | (1 << 22) | (1 << 26),
    .scl = (1 << 3) | (1 << 7) | (1 << 11) | (1 << 15) | (1 << 19) | (1 << 23) | (1 << 27)};

gci_i2c_t *gci_i2c0_init(uint8_t addr) {
  gci_i2c_t *hw = (gci_i2c_t *)calloc(1, sizeof(gci_i2c_t));
  if (hw == NULL) return NULL;
  hw->i2c  = i2c0;
  hw->addr = addr;
  return hw;
}

static int32_t gci_i2c_bus_init(uint32_t port, uint32_t baud, pin_t pin_sda, pin_t pin_scl) {
  pin_t sda, scl;
  i2c_inst_t *i2c = NULL;
  // gci_i2c_t *hw = NULL;

  if (port == 0) {
    sda = i2c0_valid.sda;
    scl = i2c0_valid.scl;
    i2c = i2c0;
    // hw = gci_i2c0_inst;
  }
  else if (port == 1) {
    sda = i2c1_valid.sda;
    scl = i2c1_valid.scl;
    i2c = i2c1;
    // hw = gci_i2c1_inst;
  }
  else return INVALID_I2C_PORT;

  // check if valid pins
  if (((1 << pin_sda) & sda) == 0) return INVALID_SDA_PIN;
  if (((1 << pin_scl) & scl) == 0) return INVALID_SCL_PIN;

  gpio_set_function(pin_sda, GPIO_FUNC_I2C);
  gpio_set_function(pin_scl, GPIO_FUNC_I2C);
  gpio_pull_up(pin_sda);
  gpio_pull_up(pin_scl);
  // Make the I2C pins available to picotool
  // THIS  WON'T WORK, cannot use variables, only constants
  // bi_decl(bi_2pins_with_func(pin_sda, pin_scl, GPIO_FUNC_I2C));

  // hw->baudrate = i2c_init(hw->i2c, baud);
  // return hw;
  return i2c_init(i2c, baud);
}

int32_t gci_i2c0_bus_init(uint32_t baud, pin_t pin_sda, pin_t pin_scl) {
  return gci_i2c_bus_init(0, baud, pin_sda, pin_scl);
}

int32_t gci_i2c1_bus_init(uint32_t baud, pin_t pin_sda, pin_t pin_scl) {
  return gci_i2c_bus_init(1, baud, pin_sda, pin_scl);
}

// int32_t gci_i2c_read(const gci_i2c_t *hw, uint8_t reg, uint8_t *dst, uint32_t size) {
int32_t gci_i2c_read(i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint8_t *dst, uint32_t size) {
  int32_t num;
  num = i2c_write_blocking(i2c, addr, &reg, 1, I2C_HOLD_BUS);
  if (num < 0) return num;
  num = i2c_read_blocking(i2c, addr, dst, size, I2C_RELEASE_BUS);
  return num;
}

int32_t gci_i2c_write(i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint8_t *src, uint32_t size) {
  uint8_t buffer[size + 1];
  buffer[0] = reg;
  // for (size_t i = 0; i < size; i++) {
  //     buffer[i + 1] = src[i];
  // }
  if (size = 1) buffer[1] = src[0];
  else {
    memcpy(&buffer[1], src, size);
  }

  // return i2c_write_blocking(i2c, addr, (uint8_t*)&msg, size+1, I2C_RELEASE_BUS);
  return i2c_write_blocking(i2c, addr, buffer, size + 1, I2C_RELEASE_BUS);
}

size_t gci_i2c_available(i2c_inst_t *i2c) { return i2c_get_read_available(i2c); }
size_t gci_i2c0_available() { return i2c_get_read_available(i2c0); }
size_t gci_i2c1_available() { return i2c_get_read_available(i2c1); }

// int32_t gci_i2c0_read(uint8_t addr, uint8_t reg, uint8_t *dst, uint32_t size) {
//   return gci_i2c_read(i2c0, addr, reg, dst, size);
// }

// int32_t gci_i2c1_read(uint8_t addr, uint8_t reg, uint8_t *dst, uint32_t size) {
//   return gci_i2c_read(i2c1, addr, reg, dst, size);
// }

// int32_t gci_i2c0_write(uint8_t addr, uint8_t reg, uint8_t *src, uint32_t size) {
//   return gci_i2c_write(i2c0, addr, reg, src, size);
// }

// int32_t gci_i2c1_write(uint8_t addr, uint8_t reg, uint8_t *src, uint32_t size) {
//   return gci_i2c_write(i2c1, addr, reg, src, size);
// }

// static
// int32_t i2c_bus_init(uint32_t port, uint32_t baud, pin_t pin_sda, pin_t pin_scl) {
//   pin_t sda, scl;
//   i2c_inst_t *i2c = NULL;
//   gci_i2c_t *hw = NULL;

//   if (port == 0) {
//     sda = i2c0_valid.sda;
//     scl = i2c0_valid.scl;
//     i2c = i2c0;
//   }
//   else if (port == 1) {
//     sda = i2c1_valid.sda;
//     scl = i2c1_valid.scl;
//     i2c = i2c1;
//   }
//   else return INVALID_I2C_PORT;

//   // check if valid pins
//   if (((1 << pin_sda) & sda) == 0) return INVALID_SDA_PIN;
//   if (((1 << pin_scl) & scl) == 0) return INVALID_SCL_PIN;

//   gpio_set_function(pin_sda, GPIO_FUNC_I2C);
//   gpio_set_function(pin_scl, GPIO_FUNC_I2C);
//   gpio_pull_up(pin_sda);
//   gpio_pull_up(pin_scl);
//   // Make the I2C pins available to picotool
//   // THIS  WON'T WORK, cannot use variables, only constants
//   // bi_decl(bi_2pins_with_func(pin_sda, pin_scl, GPIO_FUNC_I2C));

//   return i2c_init(i2c, baud);
// }

// uint32_t i2cx_init(uint32_t port, uint32_t baud, uint32_t pin_sda, uint32_t
// pin_scl) {
//   if (port != 0 && port != 1) return INVALID_PORT;
//   if (!(sda_valid[port] & (1 << pin_sda))) return INVALID_SDA_PIN;
//   if (!(scl_valid[port] & (1 << pin_scl))) return INVALID_SCL_PIN;

//   gpio_set_function(pin_sda, GPIO_FUNC_I2C);
//   gpio_set_function(pin_scl, GPIO_FUNC_I2C);
//   gpio_pull_up(pin_sda);
//   gpio_pull_up(pin_scl);
//   // Make the I2C pins available to picotool
//   // THIS  WON'T WORK, cannot use variables, only constants
//   // bi_decl(bi_2pins_with_func(pin_sda, pin_scl, GPIO_FUNC_I2C));

//   if (port == 0) return i2c_init(&i2c0_inst, baud);
//   else if (port == 1) return i2c_init(&i2c1_inst, baud);

//   return UNKNOWN;
// }

// uint32_t i2c0_init(uint32_t baud, uint32_t pin_sda, uint32_t pin_scl) {
//   return i2cx_init(0,baud,pin_sda, pin_scl);
// }

// class SensorI2C {
// protected:
//   const uint8_t addr;
//   i2c_inst_t *i2c;

// public:
// TwoWire class in picolib (gci_pico) setups the i2c0/1 so this
// class doesn't have to. This class just does i2c read/write.
//
// addr: address of sensor
// port: using i2c bus 0 or 1
// SensorI2C(uint8_t addr, const uint32_t port) : addr(addr) {
//   if (port == 0) i2c = &i2c0_inst;
//   else if (port == 1) i2c = &i2c1_inst;
// }
// ~SensorI2C() {}

// bool i2cx_write(i2c_inst_t *i2c, const uint8_t reg, const uint8_t data) {
//   uint8_t out[2] = {reg, data};
//   i2c_write_blocking(i2c, addr, out, 2, I2C_RELEASE_BUS);
//   return true;
// }

// bool i2cx_write_buffer(i2c_inst_t *i2c, const uint8_t reg, const uint32_t
// data_size, const uint8_t* data) {
// int32_t i2cx_write_buffer(const i2c_t *hw, const uint8_t reg,
//                           uint32_t data_size, const uint8_t *data) {
//   // uint8_t *out = (uint8_t*)malloc(data_size + 1);
//   // out[0] = reg;
//   // memcpy(&out[1], data, data_size);

//   // #define PICO_ERROR_GENERIC (-1)
//   uint32_t ret = i2c_write_blocking(hw->i2c, hw->addr, &reg, 1, I2C_HOLD_BUS);
//   if (ret < 0) return ret;
//   return i2c_write_blocking(hw->i2c, hw->addr, data, data_size,
//                             I2C_RELEASE_BUS);
// }

// inline
// Don't like this because "as is" there is no way to return an error
// if it occurs.
// int16_t readRegister(const uint8_t reg) {
// int8_t readRegister(const uint8_t reg) {
//   uint8_t value;
//   // return (readRegisters(reg, 1, &value) == true) ? value : 0;
//   if (readRegisters(reg, 1, &value)) return value;
//   return 0;
// }

// bool readRegister(const uint8_t reg, uint8_t *data) {
//   return readRegisters(reg, 1, data);
// }
// };

// Scans the I2C bus and returns an array of found addresses. The max number
// of slave devices is 127 (7-bit addressing), but usually it is far less.
// The function will not exceed the size of the buffer either.
//
// return: number of devices found
//
// https://github.com/raspberrypi/pico-examples/blob/master/i2c/bus_scan/bus_scan.c
// uint8_t gci_i2c_bus_scan(const uint32_t port, uint8_t *array, size_t size) {
//   size_t index = 0;
//   int ret;
//   uint8_t rxdata;
//   i2c_inst_t *i2c = (port == 0) ? &i2c0_inst : &i2c1_inst;

//   for (uint8_t addr = 0; addr < (1 << 7); ++addr) {
//     // Skip over any reserved addresses.
//     if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78) continue;

//     ret = i2c_read_blocking(i2c, addr, &rxdata, 1, false);
//     if (ret >= 0) array[index++] = addr;
//     if (index == size) return (uint8_t)index;
//   }
//   return (uint8_t)index;
// }

// int32_t gci_i2c_init(gci_i2c_t *hw, uint32_t port, uint8_t addr, uint32_t baud, pin_t pin_sda, pin_t pin_scl) {
//   pin_t sda, scl;
//   // if (port != 0 && port != 1) return INVALID_PORT;
//   // if (!(sda_valid[port] & (1 << hw->pin_sda))) return INVALID_SDA_PIN;
//   // if (!(scl_valid[port] & (1 << hw->pin_scl))) return INVALID_SCL_PIN;

//   if (hw == NULL) return I2C_PTR_NULL;

//   if (port == 0) {
//     sda = i2c0_valid.sda;
//     scl = i2c0_valid.scl;
//     hw->i2c = i2c0;
//   }
//   else if (port == 1) {
//     sda = i2c1_valid.sda;
//     scl = i2c1_valid.scl;
//     hw->i2c = i2c1;
//   }
//   else return INVALID_I2C_PORT;

//   hw->addr = addr;

//   // check if valid pins
//   if (((1 << pin_sda) & sda) == 0) return INVALID_SDA_PIN;
//   if (((1 << pin_scl) & scl) == 0) return INVALID_SCL_PIN;

//   gpio_set_function(pin_sda, GPIO_FUNC_I2C);
//   gpio_set_function(pin_scl, GPIO_FUNC_I2C);
//   gpio_pull_up(pin_sda);
//   gpio_pull_up(pin_scl);
//   // Make the I2C pins available to picotool
//   // THIS  WON'T WORK, cannot use variables, only constants
//   // bi_decl(bi_2pins_with_func(pin_sda, pin_scl, GPIO_FUNC_I2C));

//   // if (port == 0) return i2c_init(&i2c0_inst, baud);
//   // else if (port == 1) return i2c_init(&i2c1_inst, baud);
//   return i2c_init(hw->i2c, baud);
// }