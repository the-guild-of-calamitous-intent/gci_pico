
#include "fifo.h"
#include <stdint.h>
#include <string.h>

void fifo_init(volatile fifo_t *f) {
  f->tail = 0;
  f->size = 0;
  memset((void *)f->buffer, 0, FIFO_SIZE);
}

static uint16_t next_pos(const uint16_t pos) { return (pos + 1) % FIFO_SIZE; }

static bool fifo_is_full(volatile fifo_t *f) { return f->size >= FIFO_SIZE; }
static bool fifo_is_empty(volatile fifo_t *f) { return f->size == 0; }

// const uint16_t fifo_size(volatile fifo_t *f) { return f->size; }
const uint16_t fifo_capacity(volatile fifo_t *f) { return FIFO_SIZE; }

void fifo_push(volatile fifo_t *f, const uint8_t b) {
  if (fifo_is_full(f)) return; // drop new data

  f->buffer[f->tail] = b;
  f->tail            = next_pos(f->tail);
  f->size            = f->size + 1;
}

uint16_t fifo_move(volatile fifo_t *f, uint8_t *data, uint16_t size) {
  if (fifo_is_empty(f)) return 0;

  uint16_t num = (f->size > size) ? size : f->size;
  memcpy(data, (void *)f->buffer, num);

  f->tail = 0;
  f->size = 0;
  return num;
}