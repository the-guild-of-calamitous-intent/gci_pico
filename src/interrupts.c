// #include <gci_sensors/io.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gci_pico/interrupts.h"
// #include "picolib/uart.h"

gpio_levels_t is_gpio_interrupt_enabled(const pin_t gpio) {
  gpio_levels_t ret;

  // Calculate the correct interrupt enable register
  // PROC1_INTE0 covers GPIO 0-7, PROC1_INTE1 covers GPIO 8-15, etc.
  const uint reg_index  = gpio / 8;       // Register index (0 for GPIO 0-7, 1 for 8-15, etc.)
  const uint bit_offset = (gpio % 8) * 4; // Each GPIO has 4 bits (LEVEL_LOW, LEVEL_HIGH, EDGE_LOW, EDGE_HIGH)
  volatile uint32_t reg = *(volatile uint32_t *)(IO_BANK0_BASE + IO_BANK0_PROC1_INTE0_OFFSET + (reg_index * 4));

  ret.low  = (reg & (1u << (bit_offset + 0))) != 0;
  ret.high = (reg & (1u << (bit_offset + 1))) != 0;
  ret.fall = (reg & (1u << (bit_offset + 2))) != 0;
  ret.rise = (reg & (1u << (bit_offset + 3))) != 0;
  return ret;
}


void print_interrupt(const pin_t gpio) {
  gpio_levels_t irq = is_gpio_interrupt_enabled(gpio);
  printf("//   INT pin %lu: LOW[%d] HIGH[%d] RISE[%d] FALL[%d]\n",
         gpio, irq.low, irq.high, irq.rise, irq.fall);
  printf("//   IRQ Priority: %u\n", irq_get_priority(gpio));
}