#include <stdio.h>
#include "gci_pico/gci_pico.h"

constexpr pin_t ADC_PIN = A0;

int main() {
  stdio_init_all();
  wait_for_usb();

  while(adc_run_init(ADC_PIN) == false) {
    printf("*** ADC init error ***\n");
    sleep_ms(1000);
  }
  bi_decl(bi_1pin_with_name(ADC_PIN, "Analog Sensor Input"));

  while (true) {
    float val = adc_readf(ADC_PIN);
    printf(">> adc: %f\n", val);

    sleep_ms(500);
  }

  return 0;
}