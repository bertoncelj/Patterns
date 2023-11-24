#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "output.h"
#include "task.h"

#include "adt_drivers_proxy.h"
#include "console.h"

event_t led_init();
event_t led_on();
event_t led_off();
event_t led_error(void);

task_state_t task_state_led = INIT;

task_func_t led_func = {.init_task = led_init,
                        .run_task = led_on,
                        .stop_task = led_off,
                        .error_task = led_error};

char *display_led_type = "LED0";
char *display_led_on = "ON";
char *display_led_off = "OFF";

const char *led_on_msg = "meas led ON\n";
const char *led_off_msg = "meas led OFF\n";

event_t led_on() {
  output_print((uint8_t *)led_on_msg, strlen(led_on_msg));

  // Turns on LED0.
  set_imp_led_on();
  console_display_on();
  console_display_clear();

  // Diplays LED0 ON on display.
  console_display_write((uint8_t *)display_led_type);
  console_display_write_2((uint8_t *)display_led_on);
  console_display_refresh();

  task_state_led = SLEEP;
  return EVENT_DONE;
}

event_t led_off() {
  output_print((uint8_t *)led_off_msg, strlen(led_off_msg));

  // Turns off LED0.
  set_imp_led_off();
  console_display_on();
  console_display_clear();

  // Diplays LED0 OFF on display.
  console_display_write((uint8_t *)display_led_type);
  console_display_write_2((uint8_t *)display_led_off);
  console_display_refresh();

  // TODO: put some delay
  task_state_led = SLEEP;
  return EVENT_DONE;
}

event_t led_init() {

  task_state_led = RUNNING;
  return EVENT_AGAIN;
}
event_t led_error() { return EVENT_DONE; }

event_t led_task(input_state_t input_state) {
  return task_handler(input_state, task_state_led, &led_func);
}
