////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// constexpr uint16_t FIFO_SIZE = 128;
#define FIFO_SIZE 128

typedef struct {
  volatile uint8_t buffer[FIFO_SIZE];
  // uint16_t head; // read / pop
  volatile uint16_t tail; // write / push
  volatile uint16_t size;
} fifo_t;

void fifo_init(volatile fifo_t *f);
void fifo_push(volatile fifo_t *f, const uint8_t b);
// uint8_t fifo_pop(volatile fifo_t *f);
uint16_t fifo_move(volatile fifo_t *f, uint8_t *data, uint16_t size);
// bool fifo_is_full(volatile fifo_t *f);
// bool fifo_is_empty(volatile fifo_t *f);
// const uint16_t fifo_size(volatile fifo_t *f);
const uint16_t fifo_capacity(volatile fifo_t *f);

#ifdef __cplusplus
}
#endif