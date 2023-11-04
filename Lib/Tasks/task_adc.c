#include <stdint.h>
#include <stdio.h>

#include "event.h"
#include "output.h"
#include "task.h"

event_t adc_init();
event_t adc_on();
event_t adc_off();
event_t adc_error(void);

uint8_t adc_msg_on[10] = "adc_on";
uint8_t adc_msg_off[10] = "adc_off";

task_state_t task_state_adc = INIT;

// state_action_t led_state_table[INPUT_MAX][STATE_MAX];

task_func_t adc_func = {.init_task = adc_init,
                        .run_task = adc_on,
                        .stop_task = adc_off,
                        .error_task = adc_error};

event_t adc_on() {
  printf("in adc ON func\n");
  output_print(adc_msg_on, 6);

  task_state_adc = RUNNING;
  return EVENT_AGAIN;
}

event_t adc_off() {
  printf("in adc OFF func\n");
  output_print(adc_msg_off, 6);

  task_state_adc = SLEEP;
  return EVENT_DONE;
}

event_t adc_init() {
  printf("adc init()\n");

  task_state_adc = RUNNING;
  return EVENT_AGAIN;
}
event_t adc_error() {
  printf("ERROR adc \n");
  return EVENT_DONE;
}

event_t adc_task(input_state_t input_state) {
  printf("in adc TASK\n");
  return task_handler(input_state, task_state_adc, &adc_func);
}
