#include "event.h"
#include "output.h"
#include <stdint.h>
#include <stdio.h>

#define INPUT_MAX 4
event_t led_init();
event_t led_on();
event_t led_off();
event_t led_error(void);

uint8_t led_msg_on[10] = "led_on";
uint8_t led_msg_off[10] = "led_off";

task_state_t task_state_led = INIT;

typedef event_t (*led_action_func)(void);

typedef struct {
  task_state_t state;
  led_action_func action;
} state_action_t;

const state_action_t state_table[INPUT_MAX][3] = {

    // Actions for RUN input
    {
        {INIT, led_init}, // init first try
        {RUNNING, led_on},
        {SLEEP, led_off} // comment
    },
    // Actions for STOP input
    {
        {INIT, led_init}, // Error, so init
        {RUNNING, led_off},
        {SLEEP, led_off} // Already off
    },
    // Actions for TOGGLE input
    {
        {INIT, led_init}, // neki nke
        {RUNNING, led_off},
        {SLEEP, led_on} // neki neki
    },
    // Actions for NONE input
    {
        {INIT, led_init}, // comment
        {RUNNING, led_on},
        {SLEEP, led_off} // comment
    }

};

event_t led_task_handler(input_state_t input_state,
                         task_state_t task_state_led) {
  if (input_state < 0 || input_state >= INPUT_MAX || task_state_led < 0 ||
      task_state_led > SLEEP) {
    return led_error();
  }
  char *state_s[] = {"INIT", "RUNNING", "SLEEP"};

  char *input_s[] = {"RUN", "STOP", "TOGGLE", "NONE"};

  printf("LED TASK: input: %s task_state: %s \n", input_s[input_state],
         state_s[task_state_led]);
  // Retrieve the action function based on the input state and current task
  // state
  led_action_func action = state_table[input_state][task_state_led].action;

  // Call the action function if it's valid
  if (action) {
    return action();
  }

  return led_error(); // Default error case
}

event_t led_task(input_state_t input_state) {
  return led_task_handler(input_state, task_state_led);
}

event_t led_task_ex(input_state_t input_state) {
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
event_t led_error() { printf("ERROR led \n"); }
