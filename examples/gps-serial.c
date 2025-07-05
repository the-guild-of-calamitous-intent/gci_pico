#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <stdio.h>
// #include <tusb.h> // wait for USB

/*
0,178,37,23

buffer1[128]: 1,15,02,085,26,1*6D
$GPGSV,3,2,11,18,10,178,37,23,51,124,37,24,29,048,36,25,22,134,35,1*62
$GPGSV,3,3,11,28,31,212,32,31,03,21

buffer1[128]: ,1*62
$GPGSV,3,3,11,28,31,212,32,31,03,215,19,32,56,296,35,1*5A
$GAGSV,3,1,09,04,69,317,31,06,48,278,32,09,26,267,30,10,50,219

buffer1[128]: 11,02,17,316,29,10,78,342,41,12,23,098,32,15,02,085,27,1*6F
$GPGSV,3,2,11,18,10,178,37,23,51,124,37,24,29,048,36,25,22,134,35,1

buffer1[128]: 28,18,23,10,12,,,,1.11,0.58,0.95,1*03
$GNGSA,A,3,10,21,19,09,11,06,23,04,,,,,1.11,0.58,0.95,3*03
$GNGSA,A,3,35,36,19,20,22,37,

buffer1[128]: 7B
$GAGSV,1,1,01,36,21,319,,0*48
$GBGSV,2,1,06,19,64,336,31,20,49,080,31,22,18,295,16,35,18,260,23,1*72
$GBGSV,2,2,06,36,18,1

buffer1[128]: 0.92,5*05
$GPGSV,3,1,11,02,17,316,29,10,78,342,41,12,23,098,33,15,02,085,27,1*6E
$GPGSV,3,2,11,18,10,178,37,23,51,124,37,24,29

buffer1[128]: �b\(`�#�77h�����Ѫ�1��0���������$C�YH�#l\@V/��$GNRMC,225506.20,A,3854.8131

buffer1[128]: ,295,16,35,18,260,26,1*73
$GBGSV,2,2,06,36,18,185,31,37,33,057,33,1*74
$GBGSV,1,1,01,32,00,103,,0*45
$GQGSV,1,1,00,0*64
$GNG

buffer1[128]: 4,35,1*6C
$GPGSV,3,3,11,28,31,212,33,31,03,215,19,32,56,296,36,1*58
$GAGSV,3,1,10,04,69,317,29,06,48,278,31,09,26,267,31,10,50

buffer1[128]: 48,36,25,22,134,35,1*6C
$GPGSV,3,3,11,28,31,212,33,31,03,215,19,32,56,296,36,1*58
$GAGSV,3,1,10,04,69,317,29,06,48,278,31,09,2

buffer1[128]: 215,19,32,56,296,36,1*58
$GAGSV,3,1,10,04,69,317,29,06,48,278,31,09,26,267,31,10,50,219,42,7*74
$GAGSV,3,2,10,11,53,266,25,12,

buffer1[128]: 96,36,1*58


1,00,0*64
$GNGLL,3854.8

buffer1[128]: $GAGSV,3,3,11,23,38,104,38,31,21,160,36,36,31,293,30,7*48
$GAGSV,1,1,01,34,02,335,,0*45
$GBGSV,

buffer1[128]: $GBGSV,2,1,05,19,73,072,28,20,28,113,40,22,42,313,20,36,50,185,36,1*70
$GBGSV,2,2,05,37,11,041,28,1*48
$GB

buffer1[128]: $GBGSV,1,1,02,35,00,236,,44,03,278,,0*7A
$GQGSV,1,1,00,0*64
$GNGLL,3854.81310,N,07731.53233,W,000930.30,A,A*6B


buffer1[128]: $GPGSV,3,2,09,23,19,146,29,25,43,098,31,28,65,239,31,31,34,230,33,1*69
$GPGSV,3,3,09,32,69,0

buffer1[128]: $GBGSV,2,2,06,37,11,041,32,44,03,278,19,1*76
$GBGSV,1,1,01,35,00,236,,0*47
$GQG

buffer1[128]: $GNRMC,000932.50,A,38

buffer1[128]: $GAGSV,3,3,11,23,38,104,38,31,21,160,35,36,31,293,29,7*43
$GAGSV,1,1,01,34,0

buffer1[128]: $GPGSV,3,3,09,32,69,009,33,1*5A
$GPGSV,1,1,02,24,00,054,,26,01,192,,0*6F
$GAGSV,3,1,11,04,67,030,40,06,63,319,3

buffer1[128]: 

buffer1[128]: $GNRMC,000935.30,A,3854.81317,N,07731.53230,W,0.068,,290625,,,A

buffer1[128]: $GBGSV,2,2,06,37,11,041,30,44,03,278,18,1*75
$GBGSV,1,1,01,35,00,236,,0*47
$GQGSV,1,1,00,0*64
$G

buffer1[128]: $GNRMC,000936.70,A,3854.81318,N,07731.53228,W,0.065,,290625,,,A,V*01
$GN

buffer1[128]: $GNVTG,,T,,M,0.053,N,0.098,K,A*3A
$GNGGA,000937.40,3854.81319,N,07731.53227,W,1,12,0.52,106.4,M,-34.5,M,,*7A
$GNGSA,A,3,

buffer1[128]: $GAGSV,3,1,11,04,67,030,40,06,63,319,32,09,43,293,33,10,21,205,21,7*7A
$GAGSV,3,2,11,11,34,232,24,12,07,1

buffer1[128]: $GQGSV,1,1,00,0*64
$GNGLL,3854.81320,N,07731.53224,W,000938.70,A,A*62


buffer1[128]: $GNRMC,000939.50,A,3854.81320,N,0

*/

#include "gci_pico/gci_pico.h"

// #define TX_PIN 0
// #define RX_PIN 1

// constexpr uint32_t uart0_pin_tx = 12;
// constexpr uint32_t uart0_pin_rx = 13;
constexpr uint32_t uart1_pin_tx = 4;
constexpr uint32_t uart1_pin_rx = 5;

int main() {
  int i;
  int ok;
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  uint8_t buffer1[128];

  stdio_init_all();
  wait_for_usb();

  ok = uart1_init(115200, uart1_pin_tx, uart1_pin_rx);
  while (ok != 0) {
    printf("Failed to initialize uart1 %d\n", ok);
    sleep_ms(500);
  }

  bi_decl(bi_2pins_with_func(uart1_pin_rx, uart1_pin_tx, GPIO_FUNC_UART));

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  while (true) {
    gpio_put(LED_PIN, 1);
    sleep_ms(250);
    gpio_put(LED_PIN, 0);
    sleep_ms(250);

    // uart1_write(buffer1, 7);

    sleep_ms(100);

    int num1 = uart1_read(buffer1, sizeof(buffer1));
    bool nema = false;
    printf("\nbuffer1[%d]: ", num1);
    for (int i = 0; i < num1; ++i) {
      char c = (char)buffer1[i];
      if (c == '$') nema = true;
      if (nema) printf("%c", c);      
      if (c == '\n') nema = false;
    }
    printf("\n");

    sleep_ms(100);
  }
}