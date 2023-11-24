#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "output.h"
#include "task.h"

#include "console.h"

event_t lcd_init();
event_t lcd_on();
event_t lcd_off();
event_t lcd_error(void);

const char *lcd_on_msg = "lcd ON\n";
const char *lcd_off_msg = "lcd OFF\n";

task_state_t task_state_lcd = INIT;

task_func_t lcd_func = {.init_task = lcd_init,
                        .run_task = lcd_on,
                        .stop_task = lcd_off,
                        .error_task = lcd_error};

char *display_upper_all = "88.8.8.8.8*kWh";
char *display_lower_all = "88.8.8.8.8*kWhVA";

char *display_indent_up = "8.8.8";
char *display_indent_down = "8.8.8*d";

event_t lcd_on() {

  output_print((uint8_t *)lcd_on_msg, strlen(lcd_on_msg));

  console_display_on();
  console_display_clear();

  // all segments on
  console_display_test(3);
  console_display_refresh();

  task_state_lcd = SLEEP;
  return EVENT_DONE;
}

event_t lcd_off() {

  output_print((uint8_t *)lcd_off_msg, strlen(lcd_off_msg));

  console_display_on();
  console_display_clear();
  console_display_refresh();

  task_state_lcd = SLEEP;
  return EVENT_DONE;
}

event_t lcd_init() {

  task_state_lcd = RUNNING;
  return EVENT_AGAIN;
}
event_t lcd_error() { return EVENT_DONE; }

event_t lcd_task(input_state_t input_state) {
  return task_handler(input_state, task_state_lcd, &lcd_func);
}
