#include <stdlib.h>

#include "post_run_state.h"
#include "stop_state.h"

// Event handler for stop event in post run state
static void stop_state(task_state_p state) { transition_to_stop(state); }

// Transition to post run state implementation
void transition_to_post_run(task_state_p state) {
  default_impl(state);
  state->name = "Post-Run";
  // Assigning the stop event handler
  state->event_stop_func = stop_state;
  // No event handler for run event, as it should have no effect
  state->event_run_func = NULL;
}
