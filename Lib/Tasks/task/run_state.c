#include <stdio.h>

#include "task_state.h"

#include "run_state.h"
#include "stop_state.h"

#include "process_state.h"

static void stop_state(task_state_p state) {
  // run state
  printf("stop state!\n");
  transition_to_stop(state);
}

static void process_state(task_state_p state) {
  // run state
  printf("process state!\n");

  transition_to_process(state);
}

void transition_to_run(task_state_p state) {

  default_impl(state);
  state->event_stop_func = stop_state;
  state->event_process_func = process_state;
}
