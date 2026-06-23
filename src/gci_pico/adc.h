////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once

#include "typedefs.h"

// constexpr pin_t A0 = 0;
// constexpr pin_t A1 = 1;
// constexpr pin_t A2 = 2;
// constexpr pin_t A3 = 3;
#define A0 0
#define A1 1
#define A2 2
#define A3 3

// typedef enum { A0, A1, A2, A3 } adc_channel_t;

bool adc_run_init(const pin_t pin);
float adc_readf(const pin_t pin);