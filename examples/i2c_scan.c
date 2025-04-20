#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include "picolibc.h"

constexpr pin_t i2c_scl = 1;
constexpr pin_t i2c_sda = 0;

// Scans the I2C bus and returns an array of found addresses. The max number
// of slave devices is 127 (7-bit addressing), but usually it is far less.
// The function will not exceed the size of the buffer either.
//
// return: number of devices found
//
// https://github.com/raspberrypi/pico-examples/blob/master/i2c/bus_scan/bus_scan.c
int32_t i2c_bus_scan(uint8_t port, uint8_t *array, size_t size) {
  size_t index = 0;
  int ret;
  uint8_t rxdata;
  i2c_inst_t *i2c = (port == 0) ? i2c0 : i2c1;

  for (uint8_t addr = 0; addr < (1 << 7); ++addr) {
    // Skip over any reserved addresses.
    if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78) continue;

    // ret = i2c_read_blocking(i2c, addr, &rxdata, 1, false);
    ret = gci_i2c_read(i2c, addr, 0x00, &rxdata, 1);
    if (ret >= 0) array[index++] = addr;
    if (index == size) return (int32_t)index;
  }
  return (int32_t)index;
}

int main() {
  stdio_init_all();
  wait_for_usb();

  int32_t speed = gci_i2c0_bus_init(I2C_400KHZ, i2c_sda, i2c_scl);

  printf(">> i2c instance: %u baud: %u\n", 0, speed);
  printf(">> i2c SDA: %u SCL: %u\n", i2c_sda, i2c_scl);
  bi_decl(bi_2pins_with_func(i2c_sda, i2c_scl, GPIO_FUNC_I2C)); // compile info

  printf("/// SCAN I2C BUS START ///\n");

  uint8_t addrs[128];
  int num = i2c_bus_scan(0, addrs, sizeof(addrs));

  printf("Found: %d\n", num);
  for (int i=0; i < num; ++i) printf(" - 0x%X\n", (int)addrs[i]);

  while (1);

}