#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "output.h"
#include "task.h"

#include "adt_drivers_proxy.h"

event_t ee_0_init();
event_t ee_0_write();
event_t ee_0_read();
event_t ee_0_error(void);

typedef enum eeprom_e { DATA_0, DATA_1, DATA_2, DATA_3 } eeprom_data_t;

task_state_t task_state_ee_0 = INIT;

task_func_t ee_func = {.init_task = ee_0_init,
                       .run_task = ee_0_write,
                       .stop_task = ee_0_read,
                       .error_task = ee_0_error};

const char *ee_0_init_msg = "eeprom init\n";
const char *ee_0_write_addr = "eeprom write addr:0x";
const char *ee_0_read_addr = "eeprom read addr: 0x";
const char *ee_0_write_msg = "msg: ";
const char *ee_new_line = "\n";

uint8_t eeprom_buff_write_0[4] = {'a', 'b', 'c', 'd'};
uint8_t eeprom_buff_write_1[4] = {'e', 'f', 'g', 'h'};
uint8_t eeprom_buff_write_2[4] = {'i', 'j', 'k', 'l'};
uint8_t eeprom_buff_write_3[4] = {'m', 'n', 'o', 'p'};

uint16_t eeprom_address = 0x5678;
uint8_t eeprom_address_msg[5] = {0};
uint8_t eeprom_buff_read[9] = {0};

eeprom_data_t ee_data_num_g = DATA_0;

event_t ee_0_write() {
  uint8_t *ee_write_data = NULL;

  switch (ee_data_num_g) {
  case DATA_0:
    ee_write_data = eeprom_buff_write_0;
    ee_data_num_g = DATA_1;
    break;

  case DATA_1:
    ee_write_data = eeprom_buff_write_1;
    ee_data_num_g = DATA_2;
    break;

  case DATA_2:
    ee_write_data = eeprom_buff_write_2;
    ee_data_num_g = DATA_3;
    break;

  case DATA_3:
    ee_write_data = eeprom_buff_write_3;
    ee_data_num_g = DATA_0;
    break;

  default:
    // NOTHING
    break;
  }
  eeprom_write_data(ee_write_data, eeprom_address,
                    sizeof(ee_write_data)); /*Write code to write to eeprom*/

  // print address
  output_print((uint8_t *)ee_0_write_addr, strlen(ee_0_write_addr));
  transform_uint_to_ascii_hex(&eeprom_address, sizeof(eeprom_address),
                              eeprom_address_msg);
  output_print(eeprom_address_msg, 5);

  // print message
  output_print((uint8_t *)ee_0_write_msg, strlen(ee_0_write_msg));
  output_print(ee_write_data, 5);
  output_print((uint8_t *)ee_new_line, strlen(ee_new_line));

  task_state_ee_0 = SLEEP;
  return EVENT_DONE;
}

event_t ee_0_read() {

  eeprom_read_data(eeprom_buff_read, eeprom_address,
                   sizeof(eeprom_buff_write_0)); /*Write code to read what was
                                                  written to the eeprom*/

  // print address
  output_print((uint8_t *)ee_0_read_addr, strlen(ee_0_read_addr));
  output_print(eeprom_address_msg, 5);

  // print message
  output_print((uint8_t *)ee_0_write_msg, strlen(ee_0_write_msg));
  output_print(eeprom_buff_read, sizeof(eeprom_buff_write_0));
  output_print((uint8_t *)ee_new_line, strlen(ee_new_line));

  // SHUTTING DOWN
  task_state_ee_0 = SLEEP;
  return EVENT_DONE;
}

event_t ee_0_init() {
  // INIT CODE
  output_print((uint8_t *)ee_0_init_msg, strlen(ee_0_init_msg));

  task_state_ee_0 = RUNNING;
  return EVENT_AGAIN;
}

event_t ee_0_error() { return EVENT_DONE; }

event_t ee_0_task(input_state_t input_state) {
  return task_handler(input_state, task_state_ee_0, &ee_func);
}
