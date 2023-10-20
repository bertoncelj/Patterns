#ifndef _client_h_
#define _client_h_

#include "data.h"
#include "subject.h"

typedef struct client_s {
  // private date
  data_t data;
  void (*callback_fun)(void *o_object, data_t data);
} client_t;

void client_init(client_t *const self);
void client_cleanup(client_t *const self);

void client_handle_new_data(void *self, data_t data);
void client_subscribe(client_t *self, subject_t *const sub);
void client_unsubscribe(client_t *self, subject_t *const sub);

#endif //_client_h_
