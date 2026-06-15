#pragma once


#include <stdbool.h>
#include <stdint.h>
#include "gci_pico/typedefs.h"

typedef struct {
  bool low;
  bool high;
  bool fall;
  bool rise;
} gpio_levels_t;

gpio_levels_t is_gpio_interrupt_enabled(const pin_t gpio);
void print_interrupt(const pin_t gpio);