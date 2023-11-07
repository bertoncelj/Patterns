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
int8_t init_queue(queue_t *const self, uint8_t *buffer, size_t item_size,
                  size_t capacity);

// void destroy_queue(queue_t const *self);

// Methods

int8_t is_full(queue_t const *self);
int8_t is_empty(queue_t const *self);
int8_t get_size(queue_t const *self);
int8_t is_active(queue_t *self);

int8_t insert_element(queue_t *const cb, const void *item);
int8_t remove_element(queue_t *const cb, void *item);

int8_t peek_element(const queue_t *self, const size_t seek_elm, void *item);
int8_t look_first_element(queue_t *const self, void *item);

int8_t find_element(queue_t *self, const void *item_to_seacrh,
                    void *const help_item);

size_t insert_bytes(queue_t *self, const void *data, size_t btw);
size_t remove_bytes(queue_t *self, void *data, size_t btr);

size_t remaining_space(queue_t *const self);
size_t used_space(queue_t *const self);

// void print_all_elements(queue_t *const self);

// // queue_t *queue_create(void);
// void queue_destroy(queue_t const *self);

#endif // queue_h
