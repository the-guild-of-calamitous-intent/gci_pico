////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#include "gci_pico/gci_pico.h"
// #include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

bool adc_run_init(const pin_t pin) {
  // if (adc == NULL) return false;
  adc_init();

  if (pin <= 3) {
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(pin + 26);
    // adc->pin = pin;
    adc_run(true);
    return true;
  }
  return false;
}

float adc_readf(const pin_t pin) {
  adc_select_input(pin);
  uint16_t raw          = adc_read();
  const float ADC_SCALE = 3.3f / (1 << 12);
  return ADC_SCALE * raw;
}