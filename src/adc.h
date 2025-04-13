#pragma once

#include "typedefs.h"

constexpr pin_t A0 = 0;
constexpr pin_t A1 = 1;
constexpr pin_t A2 = 2;
constexpr pin_t A3 = 3;

bool adc_run_init(const pin_t pin);
float adc_readf(const pin_t pin);