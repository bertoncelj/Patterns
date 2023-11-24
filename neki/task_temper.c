#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "output.h"
#include "task.h"

#include "adt_drivers_proxy.h"

event_t mag_temper_init();
event_t mag_temper_on();
event_t mag_temper_off();
event_t mag_temper_error(void);

event_t cover_temper_init();
event_t cover_temper_on();
event_t cover_temper_off();
event_t cover_temper_error(void);

task_state_t task_state_mag_temper = INIT;
task_state_t task_state_cover_temper = INIT;

task_func_t mag_temper_func = {.init_task = mag_temper_init,
                               .run_task = mag_temper_on,
                               .stop_task = mag_temper_off,
                               .error_task = mag_temper_error};

task_func_t cover_temper_func = {.init_task = cover_temper_init,
                                 .run_task = cover_temper_on,
                                 .stop_task = cover_temper_off,
                                 .error_task = cover_temper_error};

const char *mag_temper_init_msg = "magnetic temper init\n";
const char *mag_temper_on_msg = "magnetic temper listening\n";
const char *mag_temper_off_msg = "magnetic temper OFF\n";
const char *mag_temper_task_msg = "magnetic temper status: ";
const char *mag_temper_ON_msg = "ON\n";
const char *mag_temper_OFF_msg = "OFF\n";

const char *cover_temper_init_msg = "cover temper init\n";
const char *cover_temper_on_msg = "cover temper listening\n";
const char *cover_temper_off_msg = "cover temper OFF\n";
const char *cover_temper_task_msg = "cover temper status: ";
const char *cover_temper_ON_msg = "ON\n";
const char *cover_temper_OFF_msg = "OFF\n";

uint16_t time_mag_temper_g = 0;
uint8_t mag_temper_on_trigger = 0;

uint16_t time_cover_temper_g = 0;
uint8_t cover_temper_on_trigger = 0;

event_t mag_temper_on() {
  uint16_t curr_time;

  if (mag_temper_on_trigger == 0) {
    output_print((uint8_t *)mag_temper_on_msg, strlen(mag_temper_on_msg));
    mag_temper_on_trigger = 1;
  }

  curr_time = get_RTC_time();
  if (curr_time != time_mag_temper_g) {

    output_print((uint8_t *)mag_temper_task_msg, strlen(mag_temper_task_msg));
    if (get_magnetic_temper_value() == 1) {

      // ON mag temper
      output_print((uint8_t *)mag_temper_ON_msg, strlen(mag_temper_ON_msg));
    } else {

      // OFF mag temper
      output_print((uint8_t *)mag_temper_OFF_msg, strlen(mag_temper_OFF_msg));
    }

    time_mag_temper_g = curr_time;
  }

  task_state_mag_temper = RUNNING;
  return EVENT_AGAIN;
}

event_t mag_temper_off() {
  output_print((uint8_t *)mag_temper_off_msg, strlen(mag_temper_off_msg));

  mag_temper_on_trigger = 0;
  // SHUTTING DOWN
  task_state_mag_temper = SLEEP;
  return EVENT_DONE;
}

event_t mag_temper_init() {
  // INIT CODE
  output_print((uint8_t *)mag_temper_init_msg, strlen(mag_temper_init_msg));

  task_state_mag_temper = RUNNING;
  return EVENT_AGAIN;
}

event_t mag_temper_error() { return EVENT_DONE; }

//////////////////////////////////////////////////////////////////////////////

event_t cover_temper_on() {
  uint16_t curr_time;

  if (cover_temper_on_trigger == 0) {
    output_print((uint8_t *)cover_temper_on_msg, strlen(cover_temper_on_msg));
    cover_temper_on_trigger = 1;
  }

  curr_time = get_RTC_time();
  if (curr_time != time_cover_temper_g) {

    output_print((uint8_t *)cover_temper_task_msg,
                 strlen(cover_temper_task_msg));
    if (get_cover_temper_value() == 1) {

      // ON cover temper
      output_print((uint8_t *)cover_temper_ON_msg, strlen(cover_temper_ON_msg));
    } else {

      // OFF cover temper
      output_print((uint8_t *)cover_temper_OFF_msg,
                   strlen(cover_temper_OFF_msg));
    }

    time_cover_temper_g = curr_time;
  }

  task_state_cover_temper = RUNNING;
  return EVENT_AGAIN;
}

event_t cover_temper_off() {
  output_print((uint8_t *)cover_temper_off_msg, strlen(cover_temper_off_msg));

  cover_temper_on_trigger = 0;
  // SHUTTING DOWN
  task_state_cover_temper = SLEEP;
  return EVENT_DONE;
}

event_t cover_temper_init() {
  // INIT CODE
  output_print((uint8_t *)cover_temper_init_msg, strlen(cover_temper_init_msg));

  task_state_cover_temper = RUNNING;
  return EVENT_AGAIN;
}

event_t cover_temper_error() { return EVENT_DONE; }

/////////////////////////////////////////////////////////////////////////////

event_t mag_temper_task(input_state_t input_state) {
  return task_handler(input_state, task_state_mag_temper, &mag_temper_func);
}

event_t cover_temper_task(input_state_t input_state) {
  return task_handler(input_state, task_state_cover_temper, &cover_temper_func);
}
