#include "gas_sensor.h"
#include <stdio.h>

int main(void) {

  unsigned int flow = 1;
  unsigned int n2 = 2;
  unsigned int o2 = 3;

  gas_sensor_t *p_gas_sensor = (gas_sensor_t *)malloc(sizeof(gas_sensor_t));
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);
  printf("end program!\n");
  return 0;
}
