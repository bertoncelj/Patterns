#include "client.h"
#include "subject.h"

#include <stdio.h>

void client_init(client_t *const self) {
  self->callback_fun = client_handle_new_data;
}

void client_cleanup(client_t *const self) { (void)self; }

void client_handle_new_data(void *self, data_t data) {
  ((client_t *)self)->data = data;

  printf("display module: %f, %d\n", ((client_t *)self)->data.data_f,
         ((client_t *)self)->data.data_i);
}
void client_subscribe(client_t *self, subject_t *const sub) {
  for (uint8_t idx = 0; idx < MAX_CLIENTS; idx++) {
    // Already subscriber
    if (sub->clients[idx].p_object == self) {
      return;
    }
    // Add new subscriber
    if (sub->clients[idx].p_object == NULL) {
      sub->n_client++;
      sub->clients[idx].p_object = self;
      sub->clients[idx].callback_fun = self->callback_fun;

      // Remove duplicate subscriber
      for (uint8_t left = idx + 1; left < MAX_CLIENTS; left++) {
        if (sub->clients[left].p_object == self) {
          sub->clients[left].p_object = NULL;
          sub->clients[left].callback_fun = NULL;
        }
      }
      return;
    }
  }
}

void client_unsubscribe(client_t *self, subject_t *const sub) {

  for (uint8_t idx = 0; idx < MAX_CLIENTS; idx++) {
    if (sub->clients[idx].p_object == self) {
      sub->clients[idx].p_object = NULL;
      sub->clients[idx].callback_fun = NULL;
      sub->n_client--;
      return;
    }
  }
}
