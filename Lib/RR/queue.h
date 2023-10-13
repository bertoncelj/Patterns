#ifndef _queue_h_
#define _queue_h_

#define QUEUE_MAX_SIZE 10

typedef struct queue_s queue_t;

struct queue_s {
  int buff[QUEUE_MAX_SIZE];
  void *buffer;
  int head;
  int tail;
  int size;
  int (*is_full)(queue_t const *self);
  int (*is_empty)(queue_t const *self);
  int (*get_size)(queue_t const *self);
  void (*insert_element)(queue_t *const self, const int element);
  int (*remove_element)(queue_t *const self);
};

// Constructor and destructor
void init_queue(queue_t *const self, int (*is_full_func)(queue_t const *self),
                int (*is_empty_func)(queue_t const *self),
                int (*get_size_func)(queue_t const *self),
                void (*insert_element_func)(queue_t *const self,
                                            const int element),
                int (*remove_element_func)(queue_t *const self));

void destroy_queue(queue_t const *self);

// Methods

int is_full_cb(queue_t const *self);
int is_empty_cb(queue_t const *self);
int get_size_cb(queue_t const *self);
void insert_element_cb(queue_t *const self, const int element);
void print_all_elements_cb(queue_t *const self);

int remove_element_cb(queue_t *const self);

queue_t *queue_create(void);
void queue_destroy(queue_t const *self);

#endif // queue_h
