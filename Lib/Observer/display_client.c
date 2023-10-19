#include "display_client.h"
#include "gas_data.h"
#include "gas_sensor.h"

static void clean_up_realtions(display_client_t *const self);

// Constructor and destructor
void display_client_init(display_client_t *const self) {
  self->its_gas_data = NULL;
  self->its_gas_sensor = NULL;
}

void display_client_cleanup(display_client_t *const self) {
  clean_up_realtions(self);
}

// Operations
void display_client_accept(display_client_t *const self, struct gas_data_t *g) {
  if (!self->its_gas_data) {
    self->its_gas_data = gas_data_create();
  }

  if (self->its_gas_data) {
    self->its_gas_data->flow_rate = g->flow_rate;
    self->its_gas_data->N2_conc = g->N2_conc;
    self->its_gas_data->O2_conc = g->O2_conc;
    display_client_show(self);
  }
}

void display_client_alarm(display_client_t *const self, char *alarm_msg) {
  (void)self;
  printf("ALERT!");
  printf("%s\n", alarm_msg);
}

void display_client_register(display_client_t *const self) {
  if (self->its_gas_sensor) {
    gas_sensor_subscribe(self->its_gas_sensor, self, &display_client_accept);
  }
}

void display_client_show(display_client_t *const self) {
  if (self->its_gas_sensor) {
    printf("Gas Flow Rate =%5d \n", self->its_gas_data->flow_rate);
    printf("o2 concetratiron =%2d \n", self->its_gas_data->O2_conc);
    printf("n2 concetratiron =%2d \n", self->its_gas_data->N2_conc);
  } else {
    printf("No data available\n");
  }
}

struct gas_data_t *
dispaly_client_get_its_gas_data(const display_client_t *const self) {
  return (struct gas_data_t *)self->its_gas_data;
}

void display_client_set_its_gas_data(display_client_t *const self,
                                     struct gas_data_t *p_gas_data) {
  self->its_gas_data = p_gas_data;
}

struct gas_sensor_t *
display_client_get_its_gas_sensor(const display_client_t *const self) {
  return (struct gas_sensor_t *)self->its_gas_sensor;
}

void display_client_set_its_gas_sensor(display_client_t *const self,
                                       struct gas_sensor_t *p_gas_sensor) {
  self->its_gas_sensor = p_gas_sensor;
}

display_client_t *display_client_create(void) {
  display_client_t *self = (display_client_t *)malloc(sizeof(display_client_t));
  if (self != NULL) {
    display_client_init(self);
  }
  return self;
}

void display_client_destroy(display_client_t *const self) {
  if (self != NULL) {
    display_client_cleanup(self);
  }
  free(self);
}

static void clean_up_realtions(display_client_t *const self) {
  if (self->its_gas_sensor != NULL) {
    self->its_gas_sensor = NULL;
  }

  if (self->its_gas_data != NULL) {
    self->its_gas_data = NULL;
  }
}
