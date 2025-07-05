////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#include <tusb.h> // wait for USB

void wait_for_usb() {
  while (!tud_cdc_connected()) {
    sleep_ms(100);
  }
}