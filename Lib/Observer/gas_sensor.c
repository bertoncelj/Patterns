#include "gas_sensor.h"
#include "gas_data.h"
#include "gas_notification_handle.h"

static void clean_up_relations(gas_sensor_t *const self);

// Constructor and destructor
void gas_sensor_init(gas_sensor_t *const self) {
  self->its_gas_data = NULL;
  uint8_t pos;
  for (pos = 0; pos < 100; ++pos)
    self->its_gas_NH[pos] = NULL;
}

void gas_sensor_cleanup(gas_sensor_t *const self) { clean_up_relations(self); }

void gas_sensor_dump_list(gas_sensor_t *const self) {
  uint8_t pos;
  char s[100];

  printf("Dumping registered elemetns \n");
  for (pos = 0; pos < 100; pos++) {
    if (self->its_gas_NH[pos]) {
      if (self->its_gas_NH[pos]->acceptor_ptr) {
        printf("Client: %d instance_ptr: %p , accpet pr: %p \n", pos,
               self->its_gas_NH[pos]->instance_ptr,
               self->its_gas_NH[pos]->acceptor_ptr);
      }
    }
  }
}

void gas_sensor_new_data(gas_sensor_t *const self, uint16_t flow, uint8_t n2,
                         uint8_t o2) {
  if (!self->its_gas_data)
    self->its_gas_data = gas_data_create();
  self->its_gas_data->flow_rate = flow;
  self->its_gas_data->N2_conc = n2;
  self->its_gas_data->O2_conc = o2;
  gas_sensor_notify(self);
}

void gas_sensor_notify(gas_sensor_t *const self) {
  uint8_t pos;
  char s[100];
  for (pos = 0; pos < 100; pos++) {
    if (self->its_gas_NH[pos])
      if (self->its_gas_NH[pos]->acceptor_ptr) {
        if (self->its_gas_NH[pos]->acceptor_ptr) {
          self->its_gas_NH[pos]->acceptor_ptr(self->its_gas_NH[pos],
                                              self->its_gas_data);
        }
      }
  }
}
void gas_sensor_subscribe(gas_sensor_t *const self, void *instance_ptr,
                          const gas_data_acceptor_prt *aptr) {
  struct gas_notification_handle_t *gnh;
  gnh = gas_notification_handle_create();
  gnh->instance_ptr = instance_ptr;
  gnh->acceptor_ptr = aptr;
  gas_sensor_add_get_its_gas_nh(self, gnh);
}

void gas_sensor_unsubscribe(gas_sensor_t *const self,
                            const gas_data_acceptor_prt *aptr) {
  uint8_t pos;
  for (pos = 0; pos < 100; pos++) {
    if (self->its_gas_NH[pos]) {
      if (self->its_gas_NH[pos]->acceptor_ptr == aptr) {
        gas_notification_handle_destroy(self->its_gas_NH[pos]);
        self->its_gas_NH[pos] = NULL;
      }
    }
  }
}

struct gas_data_t *gas_sensor_get_its_gas_data(const gas_sensor_t *const self) {
  return (struct gas_data_t *)self->its_gas_data;
}

void gas_sensor_set_its_gas_data(gas_sensor_t *const self,
                                 struct gas_data_t *p_gas_data_t) {
  self->its_gas_data = p_gas_data_t;
}

int gas_sensor_get_its_gas_nh(const gas_sensor_t *const self) {
  uint8_t iter = 0;
  return 0;
}

void gas_sensor_add_get_its_gas_nh(
    gas_sensor_t *const self,
    struct gas_notification_handle_t *p_gas_notification_handle) {
  uint8_t pos;
  for (pos = 0; pos < 100; pos++) {
    if (!self->its_gas_NH[pos]) {
      self->its_gas_NH[pos] = p_gas_notification_handle;
    }
  }
}

void gas_sensor_remove_get_its_gas_nh(
    gas_sensor_t *const self,
    struct gas_notification_handle_t *p_gas_notification_handle) {
  uint8_t pos;
  for (pos = 0; pos < 100; pos++) {
    if (self->its_gas_NH[pos] == p_gas_notification_handle) {
      self->its_gas_NH[pos] = NULL;
    }
  }
}

void gas_sensor_clear_its_gas_nh(gas_sensor_t *const self) {
  uint8_t pos;
  for (pos = 0; pos < 100; pos++) {
    self->its_gas_NH[pos] = NULL;
  }
}

gas_sensor_t *gas_sensor_create(void) {
  gas_sensor_t *self = (gas_sensor_t *)malloc(sizeof(gas_sensor_t));
  if (self != NULL) {
    gas_sensor_init(self);
  }
  return self;
}

void gas_sensor_destroy(gas_sensor_t *const self) {
  if (self != NULL) {
    gas_sensor_cleanup(self);
  }
  free(self);
}

static void clean_up_relations(gas_sensor_t *const self) {
  if (self->its_gas_data != NULL) {
    self->its_gas_data = NULL;
  }
}
