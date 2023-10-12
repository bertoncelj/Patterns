#include "sensor.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_sensor(sensor_t *self) {
  printf("Sensor addr: %p\n", self);
  printf("Sensor filter_frequency: %d\n", self->filter_freq);
  printf("Sensor update frequency: %d\n", self->update_freq);
  printf("Sensor value: %d\n", self->value);
  printf("Sensor interface: %d\n", self->what_kind_of_interface);
}

sensor_t *sensor_create(sensor_t *sens, int filter, int update, int value,
                        int what_kind_of_interface) {
  sens->filter_freq = filter;
  sens->update_freq = update;
  sens->value = value;
  sens->what_kind_of_interface = what_kind_of_interface;

  return sens;
}

result_t sensor_destroy(sensor_t *sens) {

  sens->filter_freq = 0;
  sens->update_freq = 0;
  sens->value = 0;
  sens->what_kind_of_interface = 0;

  return OK;
}

int get_filter_freq(const sensor_t *const self) { return self->filter_freq; }

int get_update_freq(const sensor_t *const self) { return self->update_freq; }

int get_value(const sensor_t *const self) { return self->value; }

int get_what_kind_of_interface(const sensor_t *const self) {
  return self->what_kind_of_interface;
}

void set_value(sensor_t *const self, int new_value) { self->value = new_value; }

int acquire_vlaue(sensor_t *self) {
  int *read_p, *write_p;

  switch (self->what_kind_of_interface) {

  case MEMORY_MAPPED:
    write_p = (int *)WRITE_ADDR;
    *write_p = WRITE_MASK;
    // sleep
    read_p = (int *)READ_ADDR;
    self->value = *read_p;
    break;

  case PORT_MAPPED:
    self->value = (int)SENSOR_PORT;
    break;
  }
  return self->value;
}
