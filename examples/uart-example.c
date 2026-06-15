#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "gci_pico/gci_pico.h"

constexpr pin_t TX0_PIN = 0;
constexpr pin_t RX0_PIN = 1;
constexpr pin_t TX1_PIN = 4;
constexpr pin_t RX1_PIN = 5;

#define LED_PIN PICO_DEFAULT_LED_PIN
#define LED_1HZ -1000000
#define LED_2HZ -500000

static struct repeating_timer timer;

bool blink_led(struct repeating_timer *t) {
  bool state = !gpio_get(LED_PIN);
  gpio_put(LED_PIN, state);  // toggle LED, for example
  return true;   // return false to stop the timer
}

void setup_blink_led(int rate) {
  // Option 1: microseconds
  // Negative value = "time between starts" (fixed period)
  // Positive value = "time between end of one callback and start of next"
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  add_repeating_timer_us(rate, blink_led, NULL, &timer);
}

int main() {

  int i;

  stdio_init_all();
  wait_for_usb();

  int speed = uart_open(0, 115200, TX0_PIN, RX0_PIN);
  while (speed < 0) {
    printf("Failed to initialize uart0: %d\n", speed);
    sleep_ms(500);
  }

  speed = uart_open(1, 115200, TX1_PIN, RX1_PIN);
  while (speed < 0) {
    printf("Failed to initialize uart1 %d\n", speed);
    sleep_ms(500);
  }

  bi_decl(bi_2pins_with_func(RX0_PIN, TX0_PIN, GPIO_FUNC_UART));
  bi_decl(bi_2pins_with_func(RX1_PIN, TX1_PIN, GPIO_FUNC_UART));
  
  setup_blink_led(LED_1HZ);

  uint8_t buffer0[128] = {"ping"};
  uint8_t buffer1[128] = {"pong"};

  char c = 'a';

  for (i = 0; i < 20; ++i) {

    buffer0[5] = c++;
    buffer0[6] = '\0';

    uart_write(0, buffer0, 7);
    uart_write(1, buffer1, 7);

    sleep_ms(100);

    int num0 = uart_read(0, buffer0, sizeof(buffer0));
    int num1 = uart_read(1, buffer1, sizeof(buffer1));

    printf("buffer0[%d]: ", num0);
    for (int i = 0; i < num0; ++i) printf("%c", (char)buffer0[i]);
    printf("\n");
    
    printf("buffer1[%d]: ", num1);
    for (int i = 0; i < num1; ++i) printf("%c", (char)buffer1[i]);
    printf("\n");

    sleep_ms(500);
  }

  uart_close(0);
  uart_close(1);
  printf("uarts closed\n");

  while (true) tight_loop_contents();

  return 0;
}