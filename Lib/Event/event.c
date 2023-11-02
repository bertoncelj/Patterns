#include <stdio.h>
#include <string.h>

#include "event.h"
#include "queue.h"

#include "output.h"

uint8_t text1[10] = "Hello1text";
uint8_t text2[10] = "Hello2text";
uint8_t text3[10] = "Hello3text";
struct commands_s event_table[20] =

    {
        {"led1 toggle", "<led_on_1>", 0, foo1},
        {"led2 toggle", "<led_on_2>", 0, foo2},
};

void event_init();
//
// Sample event function 1
event_t foo1() {
  printf("Executing event for LED 1 toggle.\n");
  output_print(text1, 10);

  return EVENT_DONE;
}

// Sample event function 2
event_t foo2() {
  printf("Executing event for LED 2 toggle.\n");
  output_print(text2, 10);
  return EVENT_DONE;
}
// Sample event function 2
event_t foo3() {
  static uint8_t entre = 0;
  output_print(text3, 10);
  printf("Executing event for LED 3 toggle entre %d.\n", entre++);
  if (entre == 2)
    return EVENT_DONE;
  return EVENT_AGAIN;
}
// Sample event function 2
event_t foo4() {
  static uint8_t entre = 0;
  printf("Executing event for LED 4 toggle entre %d.\n", entre++);
  if (entre == 2)
    return EVENT_DONE;
  return EVENT_AGAIN;
}
// Sample event function 2
event_t foo5() {
  printf("Executing event for LED 5 toggle.\n");
  return EVENT_DONE;
}

// Event execution function
event_t event_execute(struct commands_s *event) {

  // Check input args
  if (event == NULL)
    return 0;

  // Execute given command
  return event->event_func();
}

// Event handler to loop through all events
void event_handler(queue_t *const queue) {

  // get current commands to execute
  size_t n_comm_to_exec = queue->size;
  event_t comm_res;
  // execute commands
  for (size_t i = 0; i < n_comm_to_exec; i++) {
    commands_t comm_in_proc;
    remove_element(queue, &comm_in_proc);
    comm_res = event_execute(&comm_in_proc);

    switch (comm_res) {
    case EVENT_DONE: {
      printf("event_done\n");
      break;
    }
    case EVENT_KILL: {
      printf("event_kill\n");
      break;
    }

    case EVENT_AGAIN: {
      printf("event_again\n");
      insert_element(queue, &comm_in_proc);
      break;
    }

    case EVENT_REENTRE: {
      printf("event_reentre\n");
      break;
    }
    default:
      printf("Error!\n");
    }
  }
}
