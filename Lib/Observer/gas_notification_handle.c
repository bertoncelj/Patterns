#include "gas_notification_handle.h"

void gas_notification_handle_init(gas_notification_handle_t *const self) {
  (void)self;
}
void gas_notification_handle_cleanup(gas_notification_handle_t *const self) {
  (void)self;
}

gas_notification_handle_t *gas_notification_handle_create(void) {
  gas_notification_handle_t *self =
      (gas_notification_handle_t *)malloc(sizeof(gas_notification_handle_t));
  if (self != NULL) {
    gas_notification_handle_init(self);
  }
  return self;
}

void gas_notification_handle_destroy(gas_notification_handle_t *const self) {
  if (self != NULL)
    gas_notification_handle_cleanup(self);

  free(self);
}
