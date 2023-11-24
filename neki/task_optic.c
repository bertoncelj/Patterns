#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "output.h"
#include "task.h"

#include "console.h"

#include "adt_drivers_proxy.h"

event_t optic_telegram_init();
event_t optic_telegram_on();
event_t optic_telegram_off();
event_t optic_telegram_error(void);

event_t optic_button_init();
event_t optic_button_on();
event_t optic_button_off();
event_t optic_button_error(void);

uint8_t rtc_time_16bit_msg[5] = {0};
const char new_line = '\n';

const char *optic_telegram_msg_on = "telegram_on\n";
const char *optic_telegram_msg_off = "telegram_off\n";
const char *debug_echo_msg = "sending_optic_msg, RTC time:0x";

const char *optic_sensor_msg = "foto_value 0x";
const char *display_optic = "UUUUUU\n ";

task_state_t task_state_optic = INIT;
task_state_t task_state_optic_button = INIT;

task_func_t optic_func = {.init_task = optic_telegram_init,
                          .run_task = optic_telegram_on,
                          .stop_task = optic_telegram_off,
                          .error_task = optic_telegram_error};

task_func_t optic_button_func = {.init_task = optic_button_init,
                                 .run_task = optic_button_on,
                                 .stop_task = optic_button_off,
                                 .error_task = optic_button_error};

////////////////////////////////////////////////////

uint16_t time_telegram_g = 0;
uint16_t time_button_g = 0;

event_t optic_telegram_on() {
  uint16_t curr_time;

  // prints out message on one time
  if (task_state_optic == SLEEP) {
    output_print((uint8_t *)optic_telegram_msg_on,
                 strlen(optic_telegram_msg_on));
  }

  // prints out every RTC tick echo message on telegram
  curr_time = get_RTC_time();
  if (curr_time != time_telegram_g) {

    transform_uint_to_ascii_hex(&time_telegram_g, sizeof(time_telegram_g),
                                rtc_time_16bit_msg);

    // DEBUG rtc time
    output_print((uint8_t *)debug_echo_msg, strlen(debug_echo_msg));
    output_print(rtc_time_16bit_msg, 5);
    output_print((uint8_t *)&new_line, 1);

    send_telegram_msg((uint8_t *)display_optic, 6);
    time_telegram_g = curr_time;
  }

  task_state_optic = RUNNING;
  return EVENT_AGAIN;
}

event_t optic_telegram_off() {

  output_print((uint8_t *)optic_telegram_msg_off,
               strlen(optic_telegram_msg_off));

  task_state_optic = SLEEP;
  return EVENT_DONE;
}

event_t optic_telegram_init() {
  // Empty
  task_state_optic = RUNNING;
  return EVENT_AGAIN;
}

event_t optic_telegram_error() { return EVENT_DONE; }

/////////////////////////////// BUTTON ////////////////////////////
event_t optic_button_on() {
  uint16_t sensor_value;

  sensor_value = get_optic_sensor_value();

  transform_uint_to_ascii_hex(&sensor_value, sizeof(sensor_value),
                              rtc_time_16bit_msg);

  output_print((uint8_t *)optic_sensor_msg, 13);
  output_print(rtc_time_16bit_msg, 5);
  output_print((uint8_t *)&new_line, 1);

  task_state_optic_button = RUNNING;
  return EVENT_AGAIN;
}

event_t optic_button_off() {

  task_state_optic_button = SLEEP;
  return EVENT_DONE;
}

event_t optic_button_init() {

  task_state_optic_button = RUNNING;
  return EVENT_AGAIN;
}
event_t optic_button_error() { return EVENT_DONE; }

/////////////////////// TASKS HANDLERS ///////////////////////////
event_t optic_task(input_state_t input_state) {
  return task_handler(input_state, task_state_optic, &optic_func);
}

event_t optic_button_task(input_state_t input_state) {
  return task_handler(input_state, task_state_optic_button, &optic_button_func);
}
