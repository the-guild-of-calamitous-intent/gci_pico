#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "gci_pico/gci_pico.h"

constexpr pin_t pwm_pin = 10;

void main() {
  stdio_init_all();
  wait_for_usb();

  servo_t pwm_real = {.pin = 10};

  servo_t *pwm = &pwm_real;

  bool ok = servo_init(pwm, pwm_pin);

  while (true) {
    servo_write(pwm, 0.5);
    sleep_ms(100);
  }
}