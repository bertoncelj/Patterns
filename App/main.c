#include <stdio.h>

#include "sensor.h"

int main(void) {
  sensor_t sens_0;
  sensor_create(&sens_0, 10, 22, 123, 0);

  print_sensor(&sens_0);
  set_value(&sens_0, 99);
  printf("New value %d ", get_value(&sens_0));
  printf("End of program\n");

  return 0;
}
