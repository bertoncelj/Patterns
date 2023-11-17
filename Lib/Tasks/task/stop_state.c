#include "task_state.h"

#include "run_state.h"
#include "stop_state.h"

static void run_state(task_state_p state) {
  // run state
  transition_to_run(state);
}

void transition_to_stop(task_state_p state) {

  default_impl(state);
  state->name = "stop";
  state->event_run_func = run_state;
}
