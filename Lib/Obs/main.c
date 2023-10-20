#include "client.h"
#include "subject.h"
#include <stdio.h>

int main(void)

{
  subject_t gas_sensor;
  subject_init(&gas_sensor);

  client_t display;
  client_init(&display);

  client_t mixer;
  client_init(&mixer);

  client_subscribe(&display, &gas_sensor);
  client_subscribe(&mixer, &gas_sensor);

  subject_get_data(&gas_sensor);
  subject_get_data(&gas_sensor);
  subject_get_data(&gas_sensor);
  subject_get_data(&gas_sensor);
  subject_get_data(&gas_sensor);

  return 0;
}
