#include <stdio.h>

#include "task_state.h"

#include "process_state.h"
#include "run_state.h"
#include "stop_state.h"

static void stop_state(task_state_p state) {
  // run state
  printf("stop state!\n");
  transition_to_stop(state);
}


void transition_to_process(task_state_p state) {

  default_impl(state);
  state->event_stop_func = stop_state;
}
