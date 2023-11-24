#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "output.h"
#include "task.h"

#include "adt_drivers_proxy.h"

event_t adc_init_task();
event_t adc_on();
event_t adc_off();
event_t adc_error(void);

const char *adc_msg_on = "adc_on\n";
const char *adc_msg_off = "adc_off\n";
const char *adc_msg_running = "adc_reading\n";

task_state_t task_state_adc = INIT;

task_func_t adc_func = {.init_task = adc_init_task,
                        .run_task = adc_on,
                        .stop_task = adc_off,
                        .error_task = adc_error};

uint16_t time_adc_g = 0;

event_t adc_on() {
  uint16_t curr_time;

  if (task_state_adc == SLEEP) {
    output_print((uint8_t *)adc_msg_on, strlen(adc_msg_on));
  }

  curr_time = get_RTC_time();
  if (curr_time != time_adc_g) {
    output_print((uint8_t *)adc_msg_running, strlen(adc_msg_running));
    time_adc_g = curr_time;
  }
  task_state_adc = RUNNING;
  return EVENT_AGAIN;
}

event_t adc_off() {
  output_print((uint8_t *)adc_msg_off, strlen(adc_msg_off));

  task_state_adc = SLEEP;
  return EVENT_DONE;
}

event_t adc_init_task() {

  task_state_adc = RUNNING;
  return EVENT_AGAIN;
}
event_t adc_error() { return EVENT_DONE; }

event_t adc_task(input_state_t input_state) {
  return task_handler(input_state, task_state_adc, &adc_func);
}
