////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#include "gci_pico/pwm.h"

#include <stdbool.h>
#include <stdint.h>

#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

static constexpr uint16_t SERVO_MAX_PULSE_WIDTH = 2000UL;
static constexpr uint16_t SERVO_MIN_PULSE_WIDTH = 1000UL;

bool servo_init_adv(servo_t *pwm, pin_t pin, uint16_t max_pwm_us,
                    uint16_t min_pwm_us) {
  if (pwm == NULL) return false;

  pwm->pin = pin;
  gpio_set_function(pwm->pin, GPIO_FUNC_PWM);

  // Determine slice/channel pin belongs to
  const uint32_t slice_num = pwm_gpio_to_slice_num(pwm->pin);
  // channel   = pwm_gpio_to_channel(pwm_pin);

  // period = clkDiv / clk_sys * wrap
  // 0.02 sec = 64 / 125MHz * 39,062.5
  const uint32_t clkDiv = 64;
  const uint16_t wrap   = 39063;

  pwm->max_us = (uint16_t)((max_pwm_us - min_pwm_us) / 20E3 * wrap);
  pwm->min_us = (uint16_t)(min_pwm_us / 20E3 * wrap);

  pwm_config config = pwm_get_default_config();
  pwm_config_set_clkdiv_int(&config, clkDiv);
  pwm_config_set_wrap(&config, wrap);
  pwm_init(slice_num, &config, true);

  return true;
}

bool servo_init(servo_t *pwm, pin_t pin) {
  return servo_init_adv(pwm, pin, SERVO_MAX_PULSE_WIDTH, SERVO_MIN_PULSE_WIDTH);
}

void servo_write_us(servo_t *pwm, uint16_t pulse_width_us) {
  if (pulse_width_us > pwm->max_us) pulse_width_us = pwm->max_us;
  // pwm_set_chan_level(slice_num, channel, pulse_width_us);

  // helper, might be better to get slice/channel
  pwm_set_gpio_level(pwm->pin, pulse_width_us + pwm->min_us);
}

void servo_write(servo_t *pwm, float percent) {
  if (percent > 100.0f) percent = 100.0f;
  if (percent < 0.0f) percent = 0.0f;

  // helper, might be better to get slice/channel
  pwm_set_gpio_level(pwm->pin, percent * pwm->max_us + pwm->min_us);
  // pwm_set_chan_level(slice_num, channel, percent*max_us + min_us);
}