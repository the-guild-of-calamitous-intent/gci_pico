////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once

#include <stdint.h>

typedef uint32_t pin_t;

typedef struct {
  float x, y, z;
} vec_t;


typedef struct {
  int16_t x, y, z;
} vec_raw_t;