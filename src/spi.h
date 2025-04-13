#pragma once

// #include "hardware/gpio.h"
// #include "hardware/spi.h"
#include "typedefs.h"
#include <stdbool.h>
#include <stdint.h>

constexpr uint32_t SPI_20MHZ        = 20000000; // maximum
constexpr uint32_t SPI_10MHZ        = 10000000;
constexpr uint32_t SPI_1MHZ         = 1000000;
constexpr uint32_t SPI_100KHZ       = 100000;
constexpr uint32_t SPI_DEFAULT_BAUD = 48000; // default rate

// constexpr uint32_t SPI_8BIT_MODE    = 8;
// constexpr uint32_t SPI_16BIT_MODE   = 16;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t spi0_init(uint32_t baud, pin_t miso, pin_t mosi, pin_t sck, pin_t cs);
int spi0_transfer16(const uint16_t *out, uint16_t *in, uint32_t len);
int spi0_transfer8(const uint8_t *out, uint8_t *in, uint32_t len);

#ifdef __cplusplus
}
#endif
