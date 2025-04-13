
#include "typedefs.h"
#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <stdbool.h>
#include <stdint.h>

static uint32_t spix_init(spi_inst_t *spi, uint32_t baud, pin_t miso,
                          pin_t mosi, pin_t sck, pin_t cs) {
  // Initialize SPI channel (channel, baud rate set to 20MHz)
  baud = spi_init(spi, baud);
  // Format (channel, data bits per transfer, polarity, phase, order)
  const spi_order_t order = SPI_MSB_FIRST; // this can ONLY be MSB first
  spi_set_format(spi, 16, (spi_cpol_t)0, (spi_cpha_t)0, order);
  spi_set_slave(spi, false); // set to Master (default)

  // Map SPI signals to GPIO ports
  gpio_set_function(miso, GPIO_FUNC_SPI);
  gpio_set_function(mosi, GPIO_FUNC_SPI);
  gpio_set_function(sck, GPIO_FUNC_SPI);
  gpio_set_function(cs, GPIO_FUNC_SPI);

  return baud;
}

uint32_t spi0_init(uint32_t baud, pin_t miso, pin_t mosi, pin_t sck, pin_t cs) {
  return spix_init(spi0, baud, miso, mosi, sck, cs);
}

static int spix_transfer16(spi_inst_t *spi, const uint16_t *out, uint16_t *in,
                           uint32_t len) {
  int num = 0;
  if (spi_is_writable(spi)) {
    num = spi_write16_read16_blocking(spi, out, in, len);
  }
  return num;
}

int spi0_transfer16(const uint16_t *out, uint16_t *in, size_t len) {
  return spix_transfer16(spi0, out, in, len);
}

static int spix_transfer8(spi_inst_t *spi, const uint8_t *out, uint8_t *in,
                          uint32_t len) {
  int num = 0;
  if (spi_is_writable(spi)) {
    num = spi_write_read_blocking(spi, out, in, len);
  }
  return num;
}

int spi0_transfer8(const uint8_t *out, uint8_t *in, uint32_t len) {
  return spix_transfer8(spi0, out, in, len);
}
