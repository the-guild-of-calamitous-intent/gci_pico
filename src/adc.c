////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
// #include "pico/stdlib.h"
#include <hardware/adc.h>
#include <hardware/gpio.h>
#include "gci_pico/adc.h"


// #define ADC_12b (1 << 12)
static const float ADC_SCALE = 3.3f / ((float)(1 << 12));

bool adc_run_init(const pin_t channel) {
  adc_init();

  if (channel <= 3) {
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(channel + 26);
    // adc_run(true); // DON'T USE THIS!!!!!!!!
    return true;
  }
  return false;
}

float adc_readf(const pin_t channel) {
  adc_select_input(channel);
  // const uint16_t raw = adc_read();
  // const float ADC_SCALE = 3.3f / (1 << 12);
  return ADC_SCALE * adc_read();
}

// bool adc_run_init(const pin_t pin) {
//   // if (adc == NULL) return false;
//   adc_init();

//   if (pin <= 3) {
//     // Make sure GPIO is high-impedance, no pullups etc
//     adc_gpio_init(pin + 26);
//     // adc->pin = pin;
//     adc_run(true);
//     return true;
//   }
//   return false;
// }

// float adc_readf(const pin_t pin) {
//   adc_select_input(pin);
//   uint16_t raw          = adc_read();
//   const float ADC_SCALE = 3.3f / (1 << 12);
//   return ADC_SCALE * raw;
// }