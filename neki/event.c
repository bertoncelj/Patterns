#include <stdio.h>
#include <string.h>

#include "event.h"
#include "queue.h"

#include "event_table.h"

#include "adt_drivers_proxy.h"
#include "output.h"
//
// add + 1
#define MAX_NUM_COMMANDS 10

// Global
uint8_t buffer_g[MAX_NUM_COMMANDS * sizeof(commands_t)];
queue_t queue_g;

static void copy_and_modify_commands(const commands_t *src, commands_t *dst) {
  *dst = *src;             // Copy each structure
  dst->input_state = NONE; // Set input_state to NONE
}
// Event execution function
static event_t event_execute(struct commands_s *event) {

  // Check input args
  if (event == NULL)
    return 0;

  // Execute given command
  return event->event_func(event->input_state);
}

void event_init(void) { // init
  init_queue(&queue_g, (uint8_t *)buffer_g, sizeof(commands_t),
             MAX_NUM_COMMANDS);
}

int8_t event_insert(const commands_t *element) {
  // size_t number_cmd_to_search;
  // commands_t comm_lookup;
  //
  // number_cmd_to_search = queue_g.size;
  // for (size_t idx = 0; idx < number_cmd_to_search; idx++) {
  //   event_remove(&comm_lookup);
  //   // remove running event and add stop event
  //   if (comm_lookup.event_func == element->event_func &&
  //       comm_lookup.input_state == NONE && element->input_state == STOP) {
  //     continue;
  //   }
  //   // already running, do not add new one but add old one
  //   else if (comm_lookup.event_func == element->event_func &&
  //            comm_lookup.input_state == NONE && element->input_state == RUN)
  //            {
  //     return insert_element(&queue_g, &comm_lookup);
  //
  //   } else {
  //     // IDK?
  //   }
  //   insert_element(&queue_g, &comm_lookup);
  // }
  // // load whatever is left
  return insert_element(&queue_g, element);
}

int8_t event_remove(commands_t *element) {

  return remove_element(&queue_g, element);
}

commands_t *event_find_command(const uint8_t *search_command,
                               commands_t *result_cmd,
                               const size_t command_length) {
  // Check input
  if (search_command == NULL)
    return NULL;

  for (uint8_t idx = 0;
       idx < sizeof(avaiable_event_table) / sizeof(avaiable_event_table[0]);
       ++idx) {

    if (memcmp(avaiable_event_table[idx].command, search_command,
               command_length) == 0) {
      // Found a match, return address of this command structure
      return &avaiable_event_table[idx];
    }
  }

  // command not found
  return NULL;
}

// Event handler to loop through all events
void event_handler(void) {

  // get current commands to execute
  size_t n_comm_to_exec = queue_g.size;
  event_t comm_res;
  commands_t proc_new;

  // execute commands
  for (size_t i = 0; i < n_comm_to_exec; i++) {
    commands_t comm_in_proc;
    event_remove(&comm_in_proc);
    // print_command(&comm_in_proc);
    comm_res = event_execute(&comm_in_proc);

    switch (comm_res) {
    case EVENT_DONE: {
      break;
    }
    case EVENT_KILL: {
      break;
    }

    case EVENT_AGAIN: {
      copy_and_modify_commands(&comm_in_proc, &proc_new);
      event_insert(&proc_new);
      break;
    }

    case EVENT_REENTRE: {
      break;
    }
    default:
      // error
      break;
    }
  }
}
