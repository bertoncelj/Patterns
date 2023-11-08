#include "task_state.h"

#include "run_state.h"
#include "stop_state.h"

static void stop_state(task_state_p state) {
  // run state
  transition_to_stop(state);
}

void transition_to_run(task_state_p state) {

  default_impl(state);
  state->event_stop_func = stop_state;
}
