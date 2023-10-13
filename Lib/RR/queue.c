#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void init_queue(queue_t *const self, int (*is_full_func)(queue_t const *self),
                int (*is_empty_func)(queue_t const *self),
                int (*get_size_func)(queue_t const *self),
                void (*insert_element_func)(queue_t *const self,
                                            const int element),
                int (*remove_element_func)(queue_t *const self)) {

  self->head = 0;
  self->tail = 0;
  self->size = 0;
  // initialize member function pointers
  self->is_full = is_full_func;
  self->is_empty = is_empty_func;
  self->get_size = get_size_func;
  self->insert_element = insert_element_func;
  self->remove_element = remove_element_func;
}

void destroy_queue(queue_t const *self) {
  // TODO: rewrite and add destroy
  printf("%d", (int *)self);
};

int is_full_cb(queue_t const *self) {
  return (self->head + 1) % QUEUE_MAX_SIZE == self->tail;
}

int is_empty_cb(queue_t const *self) { return (self->head == self->tail); }

int get_size_cb(queue_t const *self) { return self->size; }

void insert_element_cb(queue_t *const self, const int element) {
  if (!self->is_full(self)) {

    printf("element in %d\n", element);
    self->buff[self->head] = element;

    printf("element in %d\n", self->buff[self->head]);
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

void print_all_elements_cb(queue_t *const self) {
  if (!self->is_empty(self)) {
    for (int idx = 0; idx < self->size; idx++) {
      printf("idx: %d -> value: %d\n", idx, self->buff[self->tail + idx]);
    }
  }
}
