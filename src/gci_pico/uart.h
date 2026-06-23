////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#ifndef __PICO_UART__
#define __PICO_UART__

#include <hardware/uart.h>
#include <stdint.h>

#include "gci_pico/typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART_INVALID_PORT -1
#define UART_INVALID_TX -2
#define UART_INVALID_RX -3

// __attribute__((deprecated)) // use uart_open
int32_t uart_open(uint8_t port, uint32_t baudrate, pin_t pin_tx, pin_t pin_rx);

int32_t uart_read(uint8_t port, uint8_t *data, uint32_t size);
int32_t uart_write(uint8_t port, uint8_t *data, uint32_t size);

bool uart_enabled(int port);
int32_t uart_available(int port);
int32_t uart_close(int port);

#ifdef __cplusplus
}
#endif

#endif // pico_uart


// typedef struct {
//   uart_inst_t *uart;
//   uint32_t baudrate;
// } gci_uart_t;

// int32_t uart0_init(uint32_t baudrate, pin_t pin_tx, pin_t pin_rx);
// uint32_t uart0_read(uint8_t *data, uint32_t size);
// void uart0_write(const uint8_t *data, uint32_t size);
// bool uart0_is_enabled();
// uint32_t uart0_available();
// void uart0_close();

// int32_t uart1_init(uint32_t baudrate, pin_t pin_tx, pin_t pin_rx);
// uint32_t uart1_read(uint8_t *data, uint32_t size);
// void uart1_write(const uint8_t *data, uint32_t size);
// bool uart1_is_enabled();
// uint32_t uart1_available();
// void uart1_close();
