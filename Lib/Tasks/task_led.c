
#include <stdint.h>
#include <stdio.h>

#include "event.h"
#include "output.h"
#include "task.h"

event_t led_init();
event_t led_on();
event_t led_off();
event_t led_error(void);

uint8_t led_msg_on[10] = "led_on";
uint8_t led_msg_off[10] = "led_off";

task_state_t task_state_led = INIT;

// state_action_t led_state_table[INPUT_MAX][STATE_MAX];
state_action_t *led_state_table[INPUT_MAX];

task_func_t led_func = {.init_task = led_init,
                        .run_task = led_on,
                        .stop_task = led_off,
                        .error_task = led_error};

event_t led_on() {
  printf("in led ON func\n");
  output_print(led_msg_on, 6);

  task_state_led = RUNNING;
  return EVENT_DONE;
}

event_t led_off() {
  printf("in led OFF func\n");
  output_print(led_msg_off, 6);

  task_state_led = SLEEP;
  return EVENT_DONE;
}

event_t led_init() {
  printf("led init()\n");

  task_state_led = RUNNING;
  return EVENT_AGAIN;
}
event_t led_error() {
  printf("ERROR led \n");
  return EVENT_DONE;
}

event_t led_task(input_state_t input_state) {
  printf("in LED TASK\n");
  static uint8_t init = 1;
  if (init) {
    printf("init state table \n");
    initialize_state_table(&led_func, led_state_table);
    init = 0;
  }
  print_state_table(led_state_table);
  return task_handler(led_state_table, INIT, task_state_led);
}
