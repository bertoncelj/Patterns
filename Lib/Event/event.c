#include <stdio.h>
#include <string.h>

#include "event.h"
#include "queue.h"

#include "output.h"

static void copy_and_modify_commands(const commands_t *src, commands_t *dst) {
  *dst = *src;             // Copy each structure
  dst->input_state = NONE; // Set input_state to NONE
}
// Event execution function
event_t event_execute(struct commands_s *event) {

  // Check input args
  if (event == NULL)
    return 0;

  // Execute given command
  return event->event_func(event->input_state);
}
void print_command(const commands_t *self) {
  char *input_s[] = {"RUN", "STOP", "TOGGLE", "NONE"};
  printf("-> command: %s %s \n", self->command, input_s[self->input_state]);
}
// Event handler to loop through all events
void event_handler(queue_t *const queue) {

  // get current commands to execute
  size_t n_comm_to_exec = queue->size;
  event_t comm_res;
  commands_t proc_new;

  // execute commands
  for (size_t i = 0; i < n_comm_to_exec; i++) {
    commands_t comm_in_proc;
    remove_element(queue, &comm_in_proc);
    print_command(&comm_in_proc);
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
      copy_and_modify_commands(&comm_in_proc, &proc_new);
      insert_element(queue, &proc_new);
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
