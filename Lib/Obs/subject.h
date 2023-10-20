#ifndef _subject_h_
#define _subject_h_

#include "data.h"

#define MAX_CLIENTS 10

// Callback function for handle notifications
// typedef void (*callback_fun)(void *o_object, data_t data);

typedef struct notifiy_s {
  void *p_object; /* Pointer to client object */
  void (*callback_fun)(void *o_object, data_t data);
} notifiy_handler_t;

typedef struct subject_s {

  data_t data;
  uint8_t n_client;
  notifiy_handler_t clients[MAX_CLIENTS];
} subject_t;

int8_t subject_init(subject_t *const self);
int8_t subject_cleanup(subject_t *const self);

void subject_get_data(subject_t *const self);
void subject_notifiy(subject_t *const self);
void subject_dumplist(subject_t *const self);

#endif //_subject_h_
