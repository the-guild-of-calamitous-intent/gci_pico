////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once
#include <stdio.h>
#include <stdlib.h>

#if defined __cplusplus
extern "C" {
#endif

// typedef struct ListNode {
//   void *data;
//   struct ListNode *next;
// } node_t;
typedef struct node_t {
  void *data;
  struct node_t *next;
} node_t;

typedef struct {
  node_t *head;
  node_t *tail;
  size_t size;
} list_t;

node_t *node_create(void *data);
bool list_init(list_t *list);
bool list_insert_end(list_t *list, void *data);
// bool list_insert_front(list_t *list, void *data); // future
bool list_pop(list_t *list, void *data);
bool list_free(list_t *list);

#if defined __cplusplus
}
#endif