#include "subject.h"
#include <stdio.h>

int8_t subject_init(subject_t *const self) {
  if (self == NULL)
    return 0;

  for (uint8_t idx = 0; idx < MAX_CLIENTS; idx++) {
    self->clients[idx].p_object = NULL;
    self->clients[idx].callback_fun = NULL;
  }
  return 1;
}

int8_t subject_cleanup(subject_t *const self) {
  if (self == NULL)
    return 0;

  for (uint8_t idx = 0; idx < MAX_CLIENTS; idx++) {
    self->clients[idx].p_object = NULL;
    self->clients[idx].callback_fun = NULL;
  }
  return 1;
}

void subject_get_data(subject_t *const self) {

  self->data.data_f = 1.0f;
  self->data.data_i = 1;

  subject_notifiy(self);
}

void subject_notifiy(subject_t *const self) {
  for (uint8_t idx = 0; idx < MAX_CLIENTS; idx++) {
    if (self->clients[idx].p_object != NULL &&
        self->clients[idx].callback_fun != NULL) {
      self->clients[idx].callback_fun(self->clients[idx].p_object, self->data);
    }
  }
}

void subject_dumplist(subject_t *const self) {
  for (uint8_t idx = 0; idx < MAX_CLIENTS; idx++) {
    if (self->clients[idx].p_object != NULL &&
        self->clients[idx].callback_fun != NULL) {
      printf("\t p_object: %p, \t callback_fun: %p",
             self->clients[idx].p_object, self->clients[idx].callback_fun);
    }
  }
}
