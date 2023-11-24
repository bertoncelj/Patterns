#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event.h"
#include "output.h"
#include "task.h"

#include "console.h"

event_t info_init();
event_t info_on();
event_t info_off();
event_t info_error(void);

task_state_t task_state_info = INIT;

task_func_t info_func = {.init_task = info_init,
                         .run_task = info_on,
                         .stop_task = info_off,
                         .error_task = info_error};

const char *display_info_name = "VER ";
const char *display_info_name_msg = "version ";
const char *display_info_ver = "0.2V\n";

event_t info_on() {

  output_print((uint8_t *)display_info_name_msg, strlen(display_info_name_msg));
  output_print((uint8_t *)display_info_ver, 4);

  // Diplays info on display.
  console_display_on();
  console_display_clear();
  console_display_write((uint8_t *)display_info_name);
  console_display_write_2((uint8_t *)display_info_ver);
  console_display_refresh();

  task_state_info = SLEEP;
  return EVENT_DONE;
}

event_t info_off() {
  task_state_info = SLEEP;
  return EVENT_DONE;
}

event_t info_init() {

  task_state_info = RUNNING;
  return EVENT_AGAIN;
}
event_t info_error() { return EVENT_DONE; }

event_t info_task(input_state_t input_state) {
  return task_handler(input_state, task_state_info, &info_func);
}
