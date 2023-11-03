#include "event.h"
#include "output.h"
#include <stdint.h>
#include <stdio.h>

event_t led_init();
event_t led_on();
event_t led_off();

uint8_t led_msg_on[10] = "led_on";
uint8_t led_msg_off[10] = "led_off";

task_state_t task_state_led = INIT;

event_t led_task(input_state_t input_state) {
  char *state_s[] = {"INIT", "RUNNING", "SLEEP"};

  char *input_s[] = {"RUN", "STOP", "TOGGLE", "NONE"};

  printf("LED TASK: input: %s task_state: %s \n", input_s[input_state],
         task_state_led[state_s]);
  event_t event_return;

  switch (input_state) {

  case RUN:
    switch (task_state_led) {
    case INIT:
      event_return = led_init();
      break;

    case RUNNING:
      event_return = led_on();
      break;

    case SLEEP:

      event_return = led_off();
      break;
    }
    break;

  case STOP:
    switch (task_state_led) {
    case INIT:
      // ERROR: task is not RUNNING, need to INIT FIRST
      event_return = led_init();
      break;

    case RUNNING:
      event_return = led_off();
      break;

    case SLEEP:
      // ALREADY KILLED:
      event_return = led_off();
      break;

      break;
    }
  case TOGGLE:
    switch (task_state_led) {
    case INIT:

      event_return = led_init();
      break;

    case RUNNING:
      event_return = led_on();
      break;

    case SLEEP:
      event_return = led_off();
      break;

      break;
    }
    break;

  case NONE:
    switch (task_state_led) {
    case INIT:

      event_return = led_init();
      break;

    case RUNNING:
      event_return = led_on();
      break;

    case SLEEP:
      event_return = led_off();
      break;
    }
    break;

  default:
    printf("ERROR \n");
    break;
  }
  return event_return;
}

event_t led_on() {
  printf("in led on func\n");
  output_print(led_msg_on, 6);

  task_state_led = RUNNING;
  return EVENT_DONE;
}

event_t led_off() {
  printf("in led off func\n");
  output_print(led_msg_off, 6);

  task_state_led = SLEEP;
  return EVENT_DONE;
}

event_t led_init() {
  printf("led init()\n");

  task_state_led = RUNNING;
  return EVENT_AGAIN;
}
