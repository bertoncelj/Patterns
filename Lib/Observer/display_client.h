#ifndef _display_client_h_
#define _display_client_h_

#include <stdio.h>
#include <stdlib.h>

#include "gas_sensor.h"

typedef struct display_client_t display_client_t;
struct display_client_t {
  struct gas_data_t *its_gas_data;
  struct gas_sensor_t *its_gas_sensor;
};

// Constructor and destructor
void display_client_init(display_client_t *const self);
void display_client_cleanup(display_client_t *const self);

// Operations
void display_client_accept(display_client_t *const self, struct gas_data_t *g);
void display_client_alarm(display_client_t *const self, char *alarm_msg);
void display_client_register(display_client_t *const self);
void display_client_show(display_client_t *const self);

struct gas_data_t *
dispaly_client_get_its_gas_data(const display_client_t *const self);
void display_client_set_its_gas_data(display_client_t *const self,
                                     struct gas_data_t *p_gas_data);

struct gas_sensor_t *
display_client_get_its_gas_sensor(const display_client_t *const self);
void display_client_set_its_gas_sensor(display_client_t *const self,
                                       struct gas_sensor_t *p_gas_sensor);

display_client_t *display_client_create(void);
void display_client_destroy(display_client_t *const self);
#endif
