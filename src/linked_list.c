////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#include "gci_pico/linked_list.h"

node_t *node_create(void *data) {
  node_t *p = (node_t *)malloc(sizeof(node_t));
  p->data   = data;
  p->next   = NULL;
  return p;
}

bool list_init(list_t *list) {
  if (list == NULL) return false;
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return true;
}

bool list_insert_end(list_t *list, void *data) {
  if (list == NULL) return false;
  // printf("insert start\n");
  node_t *node = node_create(data);

  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
    list->size = 0;
  }
  else {
    list->tail->next = node;
    list->tail       = node;
  }

  list->size += 1;
  // printf("insert: %d\n", (int)list->size);
  return true;
}

bool list_pop(list_t *list, void *data) {
  if (list == NULL || list->head == NULL || data == NULL) return false;

  // Get head node
  node_t *node = list->head;
  data         = node->data;

  // Move head to next
  list->head = node->next;
  if (list->head == NULL) list->tail = NULL; // List is now empty

  list->size--;
  free(node);
  return true;
}

bool list_free(list_t *list) {
  if (list == NULL) return false;
  // printf("start\n");
  node_t *p = NULL;
  int i     = 0;
  while (list->head != NULL) {
    // printf("loop\n");
    p          = list->head;
    list->head = list->head->next;
    // printf("%d: %p %p\n", *(int*)p->data, p, list->head);
    free(p->data);
    free(p);
  }
  return true;
}
