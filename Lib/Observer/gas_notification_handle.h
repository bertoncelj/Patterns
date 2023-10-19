#ifndef _gas_notification_handle_h_
#define _gas_notification_handle_h_

#include <stdio.h>

#include "gas_data.h"

typedef struct gas_notification_handle_t gas_notification_handle_t;

struct gas_notification_handle_t {
  void (*acceptor_ptr)(void *, struct gas_data_t *);
  void *instance_ptr;
};

void gas_notification_handle_init(gas_notification_handle_t *const self);
void gas_notification_handle_cleanup(gas_notification_handle_t *const self);

gas_notification_handle_t *gas_notification_handle_create(void);
void gas_notification_handle_destroy(gas_notification_handle_t *const self);

#endif
