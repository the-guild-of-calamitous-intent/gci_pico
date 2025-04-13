#include <gtest/gtest.h>
#include <linked_list.h>
// #include <map.h>
#include <fifo.h>
#include <stdint.h>

TEST(pico, linkedlist) {
  list_t ll;
  list_init(&ll);

  EXPECT_TRUE(true);
}

// TEST(pico, map) {
//   map_t map_real;
//   map_t *map = &map_real;
//   map_init(map, 128);
//   EXPECT_TRUE(true);
// }

TEST(pico, fifo) {
  fifo_t fifo_real;
  fifo_t *fifo = &fifo_real;
  uint8_t buffer[4];
  memset(buffer, 0, 4);

  fifo_init(fifo);
  fifo_push(fifo, 0);
  fifo_push(fifo, 1);
  fifo_push(fifo, 2);
  fifo_push(fifo, 3);

  EXPECT_EQ(fifo->size, 4);

  fifo_move(fifo, buffer, 4);
  for (uint8_t i=0; i<4; ++i) EXPECT_EQ(buffer[i], i);

  EXPECT_EQ(fifo->size, 0);
}