// #pragma once
#include <hardware/gpio.h>
#include <hardware/irq.h>
#include <hardware/uart.h>
#include <pico/stdlib.h>
#include <stdint.h>
// #include <stdio.h>
#include "fifo.h"
#include "uart.h"
#include <string.h> // memcpy

constexpr uint32_t UART_QUEUE_SIZE  = 128;
constexpr int32_t UART_INVALID_PORT = -1;
constexpr int32_t UART_INVALID_TX   = -2;
constexpr int32_t UART_INVALID_RX   = -3;

typedef struct {
  uint32_t tx;
  uint32_t rx;
} valid_uart_pins_t;

constexpr valid_uart_pins_t uart0_valid = {
    .tx = (1 << 0) | (1 << 12) | (1 << 16) | (1 << 28),
    .rx = (1 << 1) | (1 << 13) | (1 << 17) | (1 << 29)};

constexpr valid_uart_pins_t uart1_valid = {
    .tx = (1 << 4) | (1 << 8) | (1 << 20) | (1 << 24),
    .rx = (1 << 5) | (1 << 9) | (1 << 21) | (1 << 25)};

static volatile fifo_t uart0_buffer;
static volatile fifo_t uart1_buffer;

// UART interrupt handler
static void on_uart_rx(int port, uart_inst_t *uart, volatile fifo_t *fifo) {
  // uart_hw_t *hw = (uart_hw_t *)uart;

  // fifo_push(fifo, (uint8_t)hw->dr);
  // fifo_push(fifo, (uint8_t)hw->dr);
  // fifo_push(fifo, (uint8_t)hw->dr);
  // fifo_push(fifo, (uint8_t)hw->dr);

  // int cnt = 0;
  while (uart_is_readable(uart)) {
    // volatile uint8_t ch = (uint8_t)hw->dr;
    // fifo_push(fifo, ch);
    // printf("rx %d: %c\n", port, (char)ch);
    volatile uint8_t ch = uart_getc(uart);
    fifo_push(fifo, ch);
    // printf("rx %d: %c\n", port, (char)ch);
    // cnt++;
    // fifo_push(fifo, (uint8_t)hw->dr);
  }
  // printf("%d rx: %d    fifo: %d\n", port, cnt, (int)fifo->size);
}

static void uart0_irq_func(void) {
  irq_set_enabled(UART0_IRQ, false);
  irq_set_enabled(UART1_IRQ, false);
  on_uart_rx(0, uart0, &uart0_buffer);
  irq_set_enabled(UART0_IRQ, true);
  irq_set_enabled(UART1_IRQ, true);
}

static void uart1_irq_func(void) {
  irq_set_enabled(UART1_IRQ, false);
  irq_set_enabled(UART0_IRQ, false);
  on_uart_rx(1, uart1, &uart1_buffer);
  irq_set_enabled(UART1_IRQ, true);
  irq_set_enabled(UART0_IRQ, true);
}

static int32_t uartx_init(uint32_t baudrate, uint8_t port, uint8_t pin_tx,
                          uint8_t pin_rx) {
  uart_inst_t *uart     = NULL;
  uint32_t irq          = 0;
  irq_handler_t func    = NULL;
  uint32_t tx           = 0;
  uint32_t rx           = 0;
  volatile fifo_t *fifo = NULL;

  // setup values for correct port
  if (port == 0) {
    tx   = uart0_valid.tx;
    rx   = uart0_valid.rx;
    uart = uart0;
    fifo = &uart0_buffer;
    irq  = UART0_IRQ;
    func = uart0_irq_func;
  }
  else if (port == 1) {
    tx   = uart1_valid.tx;
    rx   = uart1_valid.rx;
    uart = uart1;
    fifo = &uart1_buffer;
    irq  = UART1_IRQ;
    func = uart1_irq_func;
  }
  else return UART_INVALID_PORT;

  // check if valid pins
  if (((1 << pin_tx) & tx) == 0) return UART_INVALID_TX;
  if (((1 << pin_rx) & rx) == 0) return UART_INVALID_RX;

  // queue_init(queue, sizeof(uint8_t), UART_QUEUE_SIZE);
  fifo_init(fifo);
  int32_t baud = uart_init(uart, baudrate);

  // gpio_set_function(pin_tx, GPIO_FUNC_UART);
  // gpio_set_function(pin_rx, GPIO_FUNC_UART);
  gpio_set_function(pin_tx, UART_FUNCSEL_NUM(uart, pin_tx));
  gpio_set_function(pin_rx, UART_FUNCSEL_NUM(uart, pin_rx));

  uart_set_fifo_enabled(uart, true); // Enable the UART FIFO
  uart_set_translate_crlf(uart, false);
  uart_set_hw_flow(uart, false, false);

  // Set up UART interrupt
  irq_set_exclusive_handler(irq, func);
  irq_set_enabled(irq, true);

  // IRQ will fire when 4 bytes are in FIFO RX buffer
  const bool RX_EN = true; // enable IRQ fro RX
  const bool TX_EN = false;
  uart_set_irq_enables(uart, RX_EN, TX_EN); // Enable RX interrupt only

  return 0;
}

int32_t uart0_init(uint32_t baudrate, uint8_t pin_tx, uint8_t pin_rx) {
  return uartx_init(baudrate, 0, pin_tx, pin_rx);
}

int32_t uart1_init(uint32_t baudrate, uint8_t pin_tx, uint8_t pin_rx) {
  return uartx_init(baudrate, 1, pin_tx, pin_rx);
}

static uint32_t uartx_read(uint8_t *data, uint32_t size,
                           volatile fifo_t *fifo) {
  return fifo_move(fifo, data, size);
}

uint32_t uart0_read(uint8_t *data, uint32_t size) {
  return uartx_read(data, size, &uart0_buffer);
}

uint32_t uart1_read(uint8_t *data, uint32_t size) {
  return uartx_read(data, size, &uart1_buffer);
}

void uart0_write(const uint8_t *data, uint32_t size) {
  uart_write_blocking(uart0, data, size);
}

void uart1_write(const uint8_t *data, uint32_t size) {
  uart_write_blocking(uart1, data, size);
}

uint32_t uart0_available() { return uart0_buffer.size; }
uint32_t uart1_available() { return uart0_buffer.size; }

bool uart0_is_enabled() { return uart_is_enabled(uart0); }
bool uart1_is_enabled() { return uart_is_enabled(uart1); }

void uart0_close() {
  irq_set_enabled(UART0_IRQ, false);
  uart_deinit(uart0);
}

void uart1_close() {
  irq_set_enabled(UART1_IRQ, false);
  uart_deinit(uart1);
}
