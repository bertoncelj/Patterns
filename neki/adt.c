#include "RA2A2_wdog.h"
#include <stdio.h>
#include <string.h>

#include "console.h"
#include "event.h"
#include "input.h"
#include "output.h"

const char *intro_lean = "LEAN ";
const char *intro_adt = "ADT ";

void adt(void) {

  // init
  event_init();
  output_init();

  // print intro
  console_display_clear();
  console_display_write((uint8_t *)intro_lean);
  console_display_write_2((uint8_t *)intro_adt);
  console_display_refresh();

  while (1) {
    // print_all_commands(&queue_g, avaiable_event_table);
    WATCHDOG_CLEAR_COUNT
    input();
    event_handler();
    WATCHDOG_CLEAR_COUNT
    output();
    WATCHDOG_CLEAR_COUNT
  }
}
