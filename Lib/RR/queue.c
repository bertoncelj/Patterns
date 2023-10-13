#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void init_queue(queue_t *const self, int (*is_full_func)(queue_t const *self),
                int (*is_empty_func)(queue_t const *self),
                int (*get_size_func)(queue_t const *self),
                int (*insert_element_func)(queue_t const *self),
                int (*remove_element_func)(queue_t const *self)) {

  self->head = 0;
  self->tail = 0;
  self->size = 0;
  // initialize member function pointers
  self->is_full = is_full_cb;
  self->is_empty = is_empty_func;
  self->get_size = get_size_cb;
  self->insert_element = insert_element_cb;
  self->remove_element = remove_element_cb;
}

void destroy_queue(queue_t const *self){};

int is_full_cb(queue_t const *self) {
  return (self->head + 1) % QUEUE_MAX_SIZE == self->tail;
}

int is_empty_cb(queue_t const *self) { return (self->head == self->tail); }

int get_size_cb(queue_t const *self) { return self->size; }

void insert_element_cb(queue_t *const self, const int element) {
  if (!self->is_full(self)) {
    self->buff[self->head] = element;
    self->head = (self->head + 1) % QUEUE_MAX_SIZE;
    ++self->size;
  }
}

int remove_element_cb(queue_t *const self) {
  int value = 0;
  if (!self->is_empty(self)) {
    value = self->buff[self->tail];
    self->tail = (self->tail + 1) % QUEUE_MAX_SIZE;
    --self->size;
  }
  // make return Some or None
  return value;
}
