#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/dma.h"
#include "hardware/irq.h"


// | Feature        | RP2040  | RP2350 |
// |----------------|---------|--------|
// | Channels       | 12      | 16
// | Interrupts     | 2       | 4
// | Transfer Count | Limited | Infinite
// | HW Timers      | 1       | 2
// | Alarms/Timer   | 4       | 4
// | Counter Width  | 64-bit  | 64-bit
// | Timer Res      | 1 usec  | 1 usec

// uint32_t current_core = get_core_num();

// Configuration
#define UART0_BAUD 115200
#define UART1_BAUD 115200

// Pin assignments (standard defaults)
#define UART0_TX_PIN 0
#define UART0_RX_PIN 1
#define UART1_TX_PIN 4
#define UART1_RX_PIN 5

// Buffers (adjust sizes as needed)
#define BUFFER_SIZE 256

// DMA channels (will be claimed)
static int dma_tx0 = -1;
static int dma_rx0 = -1;
static int dma_tx1 = -1;
static int dma_rx1 = -1;

// Global buffers for simplicity (one per UART for demo)
static uint8_t rx_buffer0[BUFFER_SIZE];
static uint8_t rx_buffer1[BUFFER_SIZE];

// Simple blocking wait helper
static void dma_wait(int channel) {
    dma_channel_wait_for_finish_blocking(channel);
}

// Abstract init for a UART with DMA
static void uart_dma_init(uart_inst_t *uart, uint baudrate, uint tx_pin, uint rx_pin,
                          int *dma_tx_chan, int *dma_rx_chan) {
    // Initialize UART
    uart_init(uart, baudrate);
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);

    // Claim DMA channels
    *dma_tx_chan = dma_claim_unused_channel(true);
    *dma_rx_chan = dma_claim_unused_channel(true);

    // Configure TX DMA (common setup)
    dma_channel_config tx_config = dma_channel_get_default_config(*dma_tx_chan);
    channel_config_set_transfer_data_size(&tx_config, DMA_SIZE_8);
    channel_config_set_read_increment(&tx_config, true);
    channel_config_set_write_increment(&tx_config, false);
    channel_config_set_dreq(&tx_config, uart_get_dreq(uart, true));
    dma_channel_configure(*dma_tx_chan, &tx_config, &uart_get_hw(uart)->dr, NULL, 0, false);

    // Configure RX DMA
    dma_channel_config rx_config = dma_channel_get_default_config(*dma_rx_chan);
    channel_config_set_transfer_data_size(&rx_config, DMA_SIZE_8);
    channel_config_set_read_increment(&rx_config, false);
    channel_config_set_write_increment(&rx_config, true);
    channel_config_set_dreq(&rx_config, uart_get_dreq(uart, false));
    dma_channel_configure(*dma_rx_chan, &rx_config, NULL, &uart_get_hw(uart)->dr, 0, false);
}

// Abstract write: sends len bytes from src using DMA (blocking for simplicity)
void uart_write(uart_inst_t *uart, const uint8_t *src, size_t len, int dma_tx_chan) {
    if (len == 0) return;
    dma_channel_set_read_addr(dma_tx_chan, src, false);
    dma_channel_set_trans_count(dma_tx_chan, len, true);
    dma_wait(dma_tx_chan);
}

// Abstract read: reads up to len bytes into dst using DMA (blocking, starts transfer)
size_t uart_read(uart_inst_t *uart, uint8_t *dst, size_t len, int dma_rx_chan) {
    if (len == 0) return 0;
    dma_channel_set_write_addr(dma_rx_chan, dst, false);
    dma_channel_set_trans_count(dma_rx_chan, len, true);
    dma_wait(dma_rx_chan);
    // For real use, you might check uart_is_readable or use interrupts for variable length
    return len;  // Assume full transfer for demo
}

int main() {
    stdio_init_all();

    printf("Pico UART0/1 DMA Example\n");

    // Init UART0 with DMA
    uart_dma_init(uart0, UART0_BAUD, UART0_TX_PIN, UART0_RX_PIN, &dma_tx0, &dma_rx0);

    // Init UART1 with DMA
    uart_dma_init(uart1, UART1_BAUD, UART1_TX_PIN, UART1_RX_PIN, &dma_tx1, &dma_rx1);

    // Example loop: echo between UART0 and UART1 (connect TX0->RX1 and TX1->RX0 for test)
    while (true) {
        // const char *test_msg = "Hello from UART0 via DMA!\n";
        // uart_write(uart0, (const uint8_t *)test_msg, strlen(test_msg), dma_tx0);

        // // Read back on UART1
        // size_t read_len = uart_read(uart1, rx_buffer1, BUFFER_SIZE, dma_rx1);
        // if (read_len > 0) {
        //     printf("UART1 received: %.*s", (int)read_len, rx_buffer1);
        // }

        // sleep_ms(1000);

        // // Reverse direction example
        // const char *test_msg2 = "Hello from UART1 via DMA!\n";
        // uart_write(uart1, (const uint8_t *)test_msg2, strlen(test_msg2), dma_tx1);

        // read_len = uart_read(uart0, rx_buffer0, BUFFER_SIZE, dma_rx0);
        // if (read_len > 0) {
        //     printf("UART0 received: %.*s", (int)read_len, rx_buffer0);
        // }


        size_t read_len = uart_read(uart0, rx_buffer0, BUFFER_SIZE, dma_rx0);
        if (read_len > 0) {
          fwrite(rx_buffer0, 1, read_len, stdout);
          fflush(stdout);
        }

        sleep_ms(10);
    }

    // Cleanup (unreachable in this loop)
    dma_channel_unclaim(dma_tx0);
    dma_channel_unclaim(dma_rx0);
    dma_channel_unclaim(dma_tx1);
    dma_channel_unclaim(dma_rx1);
    uart_deinit(uart0);
    uart_deinit(uart1);

    return 0;
}