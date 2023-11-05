#include <stdio.h>
#include <string.h>

#include "queue.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

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

int8_t find_element(queue_t *self, const void *item_to_seacrh,
                    void *const help_item) {

  if (is_empty(self))
    return 0;

  for (uint8_t idx = 0; idx < self->size; idx++) {

    if (peek_element(self, idx, help_item)) {
      if (memcmp(help_item, item_to_seacrh, self->item_size) == 0) { // found it
        return 1;
      }
    }
  }
  return 0;
}

int8_t insert_bytes(queue_t *self, const void *data, size_t btw) {
  uint16_t free_space;
  uint16_t copy_size;

  // Check inputs
  // item size must be 1
  if (self == NULL || data == NULL || btw == 0 || self->item_size != 1)
    return 0;

  // Check if full
  if (is_full(self) || self->size == self->capacity - 1)
    return 0;

  // Check if there is aviable free space to write
  free_space = remaining_space(self);
  btw = MIN(free_space, btw);
  if (btw == 0)
    return 0;

  // write data into first part
  copy_size = self->capacity - self->head;
  memcpy(&self->buffer[self->head], data, copy_size);
  self->head = (self->head + copy_size) %
               (self->capacity * self->item_size); // item_size must be 1
  self->size += copy_size;
  btw -= copy_size;

  // write data in top part
  if (btw > 0) {
    memcpy(&self->buffer[self->head], &data[copy_size], btw);
    self->head = (self->head + btw) %
                 (self->capacity * self->item_size); // item_size must be 1
  }

  // check if there was no buffer overflow
  if (self->head >= self->capacity)
    self->head = 0;

  return btw + copy_size;
}

// from 0 .. size - 1
int8_t peek_element(const queue_t *self, const size_t seek_elm, void *item) {
  uint16_t item_pos;
  if (self == NULL || is_empty(self))
    return 0;

  if (seek_elm > self->size)
    return 0;

  item_pos = (self->tail + (self->item_size * (seek_elm))) %
             (self->capacity * self->item_size);
  memcpy(item, &self->buffer[item_pos], self->item_size);

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
