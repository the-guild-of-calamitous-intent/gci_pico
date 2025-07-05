#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "gci_pico/gci_pico.h"

constexpr pin_t MISO           = 0;
constexpr pin_t MOSI           = 1;
constexpr pin_t SCK            = 2;
constexpr pin_t CS             = 3;
constexpr uint32_t BUFFER_SIZE = 10;

void main() {
  stdio_init_all();
  wait_for_usb();

  uint32_t baud = spi0_init(SPI_1MHZ, MISO, MOSI, SCK, CS);
  uint8_t outbuffer[BUFFER_SIZE];
  uint8_t inbuffer[BUFFER_SIZE];

  while (true) {
    int num = spi0_transfer8(outbuffer, inbuffer, BUFFER_SIZE);
    sleep_ms(100);
  }
}