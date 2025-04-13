////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once

#include "typedefs.h"
#include <stdbool.h>
#include <stdint.h>

#if defined __cplusplus
extern "C" {
#endif

typedef struct {
  // uint32_t slice_num;
  pin_t pin;
  uint16_t max_us;
  uint16_t min_us;
} servo_t;

bool servo_init(servo_t *pwm, pin_t pin);
bool servo_init_adv(servo_t *pwm, pin_t pin, uint16_t max_pwm_us,
                    uint16_t min_pwm_us);
void servo_write_us(servo_t *pwm, uint16_t pulse_width_us);
void servo_write(servo_t *pwm, float percent);

#if defined __cplusplus
}
#endif