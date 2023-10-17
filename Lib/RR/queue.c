#include <stdio.h>
#include <string.h>

#include "queue.h"

int8_t init_queue(queue_t *const self, uint8_t *buffer, size_t item_size,
                  size_t capacity) {
  // Check if inputs are correct format
  if (self == NULL || buffer == NULL || item_size == 0 || capacity == 0)
    return 0;

  self->buffer = buffer;
  self->head = 0;
  self->tail = 0;
  self->size = 0;
  self->capacity = capacity;
  self->item_size = item_size;

  return 1;
}

int8_t is_full(queue_t const *self) {
  size_t umesni =
      (self->head + self->item_size) % (self->item_size * self->capacity);

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
  //
  // Check inputs
  if (self == NULL || item == NULL)
    return 0;

  // Check if full
  if (is_full(self) || self->size == self->capacity - 1)
    return 0;

  memcpy(&self->buffer[self->head], item, self->item_size);
  self->head =
      (self->head + self->item_size) % (self->capacity * self->item_size);
  self->size++;

  return 1;
}

int8_t remove_element(queue_t *const self, void *item) {
  // Check inputs
  if (self == NULL || item == NULL)
    return 0;

  // dobule check if empty
  if (is_empty(self) || self->size == 0)
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

size_t used_space(queue_t *const self) {

  // Check input
  size_t full_items = 0;
  if (self == NULL)
    return 0;

  // empty
  if (self->head == self->tail)
    full_items = 0;

  // full items
  else if (self->head > self->tail)
    full_items = self->head - self->tail;

  // full items with overflow
  else
    full_items = (self->capacity * self->item_size) - (self->tail - self->head);

  return full_items;
}

size_t remaining_space(queue_t *const self) {

  // Check input
  size_t empty_items = 0;
  if (self == NULL)
    return 0;

  // empty
  if (self->head == self->tail)
    empty_items = self->capacity * self->item_size;

  // non-empty
  else if (self->tail > self->head)
    empty_items = self->tail - self->head;

  // non-empty with overflow
  else
    empty_items =
        (self->capacity * self->item_size) - (self->head - self->tail);

  // free is one less then full avaible buffer
  return empty_items - self->item_size;
}
