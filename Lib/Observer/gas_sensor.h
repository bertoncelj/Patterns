#ifndef _gas_sensor_h_
#define _gas_sensor_h_

#include <stdio.h>
#include <stdlib.h>

#include "gas_notification_handle.h"
#include "gas_sensor.h"

/* the function pointer type

The first value of the function pointer is to the instance

data of the class. The second is a ptr to the new gas data

*/

typedef void (*gas_data_acceptor_prt)(void *, struct gas_data_t *);

struct gas_notification_handle_t;

typedef struct gas_sensor_s {

  struct gas_data_t *its_gas_data;
  struct gas_notification_handle_t *its_gas_NH[100];
} gas_sensor_t;

// Constructor and destructor
void gas_sensor_init(gas_sensor_t *const self);
void gas_sensor_cleanup(gas_sensor_t *const self);

void gas_sensor_dump_list(gas_sensor_t *const self);
void gas_sensor_new_data(gas_sensor_t *const self, uint16_t flow, uint8_t n2,
                         uint8_t o2);
void gas_sensor_notify(gas_sensor_t *const self);
void gas_sensor_subscribe(gas_sensor_t *const self, void *instance_ptr,
                          const gas_data_acceptor_prt *aptr);
void gas_sensor_unsubscribe(gas_sensor_t *const self,
                            const gas_data_acceptor_prt *aptr);
struct gas_data_t *gas_sensor_get_its_gas_data(const gas_sensor_t *const self);
void gas_sensor_set_its_gas_data(gas_sensor_t *const self,
                                 struct gas_data_t *p_gas_data_t);

int gas_sensor_get_its_gas_nh(const gas_sensor_t *const self);

void gas_sensor_add_get_its_gas_nh(
    gas_sensor_t *const self,
    struct gas_notification_handle_t *p_gas_notification_handle);

void gas_sensor_remove_get_its_gas_nh(
    gas_sensor_t *const self,
    struct gas_notification_handle_t *p_gas_notification_handle);

void gas_sensor_clear_its_gas_nh(gas_sensor_t *const self);

gas_sensor_t *gas_sensor_create(void);
void gas_sensor_destroy(gas_sensor_t *const self);

#endif
