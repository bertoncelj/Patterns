#include <stdio.h>

#include "gas_sensor.h"

#include "display_client.h"

int main(void) {

  display_client_t *p_display_client = display_client_create();
  display_client_register(p_display_client);

  display_client_alarm(p_display_client, "hello");

  unsigned int flow = 1;
  unsigned int n2 = 2;
  unsigned int o2 = 3;

  gas_sensor_t *p_gas_sensor = (gas_sensor_t *)malloc(sizeof(gas_sensor_t));
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);
  gas_sensor_new_data(p_gas_sensor, flow, n2, o2);

  display_client_destroy(p_display_client);

  printf("end program!\n");
  return 0;
}
