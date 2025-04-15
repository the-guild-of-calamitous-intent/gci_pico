
#include "picolibc.h"

// Scans the I2C bus and returns an array of found addresses. The max number
// of slave devices is 127 (7-bit addressing), but usually it is far less.
// The function will not exceed the size of the buffer either.
//
// return: number of devices found
//
// https://github.com/raspberrypi/pico-examples/blob/master/i2c/bus_scan/bus_scan.c
uint8_t i2c_bus_scan(i2c_inst_t *i2c, uint8_t *array, size_t size) {
  size_t index = 0;
  int ret;
  uint8_t rxdata;
  // i2c_inst_t *i2c = (port == 0) ? &i2c0_inst : &i2c1_inst;

  for (uint8_t addr = 0; addr < (1 << 7); ++addr) {
    // Skip over any reserved addresses.
    if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78) continue;

    ret = i2c_read_blocking(i2c, addr, &rxdata, 1, false);
    if (ret >= 0) array[index++] = addr;
    if (index == size) return (uint8_t)index;
  }
  return (uint8_t)index;
}

int main() {
  gci_i2c_t i2c_real = {
    .i2c = i2c0,
    .addr = 0x11
  };

  gci_i2c_t *i2c = &i2c_real;

  int32_t buad = gci_i2c_init(0,I2C_400KHZ,0,1);

  uint8_t addrs[128];
  i2c_bus_scan(i2c0,addrs, sizeof(addrs));
}