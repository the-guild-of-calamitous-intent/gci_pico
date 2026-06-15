#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "gci_pico/gci_pico.h"

constexpr pin_t PWM_PIN = 10;

void main() {
  stdio_init_all();
  wait_for_usb();

  servo_t pwm;

  bool ok = servo_init(&pwm, PWM_PIN);

  bi_decl(bi_pin_mask_with_name(PWM_PIN, "PWM Pin"));

  float width = 0.0f;
  while (true) {
    width += 0.1f;
    width = (width <= 1.0f) ? width : 0.0f;
    servo_write(&pwm, width);
    sleep_ms(100);
  }
}