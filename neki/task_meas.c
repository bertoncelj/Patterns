#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "output.h"
#include "task.h"

#include "adt_drivers_proxy.h"
#include "console.h"

void task_meas(input_state_t state);

event_t meas_init();
event_t meas_on();
event_t meas_off();
event_t meas_error(void);

task_state_t task_state_meas = INIT;

task_func_t meas_func = {.init_task = meas_init,
                         .run_task = meas_on,
                         .stop_task = meas_off,
                         .error_task = meas_error};

const char *meas_init_msg = "meas INIT\n";
const char *meas_on_msg = "meas ON\n";
const char *meas_off_msg = "meas OFF\n";
const char *meas_task_msg = "meas task\n";

uint16_t time_meas_g = 0;
uint8_t meas_on_trigger = 0;

event_t meas_on() {
  uint16_t curr_time;

  if (meas_on_trigger == 0) {
    output_print((uint8_t *)meas_on_msg, strlen(meas_on_msg));
    meas_on_trigger = 1;
  }

  curr_time = get_RTC_time();
  if (curr_time != time_meas_g) {
    output_print((uint8_t *)meas_task_msg, strlen(meas_task_msg));

    time_meas_g = curr_time;
  }

  task_state_meas = RUNNING;
  return EVENT_AGAIN;
}

event_t meas_off() {
  output_print((uint8_t *)meas_off_msg, strlen(meas_off_msg));

  meas_on_trigger = 0;
  // SHUTTING DOWN
  task_state_meas = SLEEP;
  return EVENT_DONE;
}

event_t meas_init() {
  // INIT CODE
  output_print((uint8_t *)meas_init_msg, strlen(meas_init_msg));

  task_state_meas = RUNNING;
  return EVENT_AGAIN;
}

event_t meas_error() { return EVENT_DONE; }

event_t meas_task(input_state_t input_state) {
  return task_handler(input_state, task_state_meas, &meas_func);
}
