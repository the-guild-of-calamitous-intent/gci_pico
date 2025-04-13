#pragma once

#include "hardware/watchdog.h"

/*
void watchdog_reboot (uint32_t pc, uint32_t sp, uint32_t delay_ms)
  Define actions to perform at watchdog timeout.

void watchdog_start_tick (uint cycles)
  Start the watchdog tick.

void watchdog_update (void)
  Reload the watchdog counter with the amount of time set in watchdog_enable.

void watchdog_enable (uint32_t delay_ms, bool pause_on_debug)
  Enable the watchdog.

void watchdog_disable (void)
  Disable the watchdog.

bool watchdog_caused_reboot (void)
  Did the watchdog cause the last reboot?

bool watchdog_enable_caused_reboot (void)
  Did watchdog_enable cause the last reboot?

uint32_t watchdog_get_time_remaining_ms (void)
  Returns the number of microseconds before the watchdog will reboot the chip.
*/

// existing watch functions:
//
// watchdog_enable(delay_ms, true);
// watchdog_update();

// uint32_t watchdog_time_remaining_us() { return watchdog_get_count(); }