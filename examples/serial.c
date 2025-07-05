#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "gci_pico/gci_pico.h"

constexpr uint32_t uart0_pin_tx = 12;
constexpr uint32_t uart0_pin_rx = 13;
constexpr uint32_t uart1_pin_tx = 4;
constexpr uint32_t uart1_pin_rx = 5;

int main() {

  int i;

  stdio_init_all();
  wait_for_usb();

  int ok = uart0_init(115200, uart0_pin_tx, uart0_pin_rx);
  while (ok != 0) {
    printf("Failed to initialize uart0: %d\n", ok);
    sleep_ms(500);
  }

  ok = uart1_init(115200, uart1_pin_tx, uart1_pin_rx);
  while (ok != 0) {
    printf("Failed to initialize uart1 %d\n", ok);
    sleep_ms(500);
  }

  bi_decl(bi_2pins_with_func(uart0_pin_rx, uart0_pin_tx, GPIO_FUNC_UART));
  bi_decl(bi_2pins_with_func(uart1_pin_rx, uart1_pin_tx, GPIO_FUNC_UART));

  // struct linked_list ll;
  // ll_init(&ll);

  // struct map m;
  // map_init(&m, 128);

  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  uint8_t buffer0[128] = {"ping"};
  uint8_t buffer1[128] = {"pong"};
  char c               = 'a';

  for (i = 0; i < 20; ++i) {
    gpio_put(LED_PIN, 1);
    sleep_ms(250);
    gpio_put(LED_PIN, 0);
    sleep_ms(250);

    buffer0[5] = c++;
    buffer0[6] = '\0';

    uart0_write(buffer0, 7);
    uart1_write(buffer1, 7);

    sleep_ms(100);

    int num0 = uart0_read(buffer0, sizeof(buffer0));
    int num1 = uart1_read(buffer1, sizeof(buffer1));

    printf("buffer0[%d]: ", num0);
    for (int i = 0; i < num0; ++i)
      printf("%c", (char)buffer0[i]);
    printf("\nbuffer1[%d]: ", num1);
    for (int i = 0; i < num1; ++i)
      printf("%c", (char)buffer1[i]);
    printf("\n");

    sleep_ms(100);
  }

  uart0_close();
  uart1_close();
  printf("uarts closed\n");

  while (true)
    ;
}