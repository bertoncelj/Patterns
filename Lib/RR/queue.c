#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

void init_queue(queue_t *const self, uint8_t *buffer, size_t item_size,
                size_t capacity) {
  // Safty check
  // if (buffer != NULL)
  // return;
  self->buffer = buffer;
  self->head = 0;
  self->tail = 0;
  self->size = 0;
  self->capacity = capacity;
  self->item_size = item_size;
}

int8_t is_full(queue_t const *self) {
  printf("self->head: %zu\n", self->head);
  printf("self->item_size: %zu\n", self->item_size);
  printf("self->capacity: %zu\n", self->capacity);
  printf("self->tail: %zu\n", self->tail);
  printf("self->size: %zu\n", self->size);
  size_t umesni =
      (self->head + self->item_size) % (self->item_size * self->capacity);

  printf("umesni: %zu\n", umesni);
  printf("result: %d\n", (int)umesni == (int)self->tail);

  return umesni == self->tail;
}

int8_t is_active(queue_t *self) {
  if (self != NULL && self->buffer != NULL && self->capacity > 0) {
    return 1;
  } else {
    return -1;
  }
}

int8_t is_empty(queue_t const *self) { return (self->head == self->tail); }

int8_t get_size(queue_t const *self) { return self->size; }

int8_t insert_element(queue_t *self, const void *item) {
  // Better this one
  if (is_full(self))
    return 0;
  printf("after full\n");
  if (self->size == self->capacity)
    return 0;
  printf("next!\n");

  memcpy(&self->buffer[self->head], item, self->item_size);
  self->head =
      (self->head + self->item_size) % (self->capacity * self->item_size);
  self->size++;

  return 1;
}

int8_t remove_element(queue_t *const self, void *item) {
  if (self->size == 0)
    return 0;

  memcpy(item, &self->buffer[self->tail], self->item_size);
  self->tail =
      (self->tail + self->item_size) % (self->capacity * self->item_size);
  self->size--;

  return 1;
}

int8_t look_first_element(queue_t *const self, void *item) {
  if (self->size == 0)
    return 0;

  memcpy(item, &self->buffer[self->tail], self->item_size);
  return 1;
}
