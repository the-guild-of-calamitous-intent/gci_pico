////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t pin_t;

//[[deprecated]]
int32_t uart0_init(uint32_t baudrate, uint8_t pin_tx, uint8_t pin_rx);
bool uart0_is_enabled();
uint32_t uart0_read(uint8_t *data, uint32_t size);
void uart0_write(const uint8_t *data, uint32_t size);
uint32_t uart0_available();
void uart0_close();

int32_t uart1_init(uint32_t baudrate, uint8_t pin_tx, uint8_t pin_rx);
bool uart1_is_enabled();
uint32_t uart1_read(uint8_t *data, uint32_t size);
void uart1_write(const uint8_t *data, uint32_t size);
uint32_t uart1_available();
void uart1_close();

#ifdef __cplusplus
}
#endif
