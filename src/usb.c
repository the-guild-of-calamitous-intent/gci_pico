
#include <tusb.h> // wait for USB

void wait_for_usb() {
  while (!tud_cdc_connected()) {
    sleep_ms(100);
  }
}