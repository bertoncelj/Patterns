#ifndef _queue_h_
#define _queue_h_

#include <stdint.h>

#define QUEUE_MAX_SIZE 10

typedef struct queue_s queue_t;

struct queue_s {
  uint8_t *buffer;
  uint16_t head;
  uint16_t tail;
  size_t size;
  size_t item_size;
  size_t capacity;
};

// Constructor and destructor
void init_queue(queue_t *const self, uint8_t *buffer, size_t item_size,
                size_t capacity);

// void destroy_queue(queue_t const *self);

// Methods

int8_t is_full(queue_t const *self);
int8_t is_empty(queue_t const *self);
int8_t get_size(queue_t const *self);
int8_t is_active(queue_t *self);

int8_t insert_element(queue_t *const cb, const void *item);
int8_t remove_element(queue_t *const cb, void *item);

// void print_all_elements(queue_t *const self);

// // queue_t *queue_create(void);
// void queue_destroy(queue_t const *self);

#endif // queue_h
