#include "state_start.h"
#include "watch_state_internal.h"

#include "state_stop.h"

static void stop_watch(watch_state_p state) {
  printf("stop watch!\n");
  transition_to_stop(state);
}

void transition_to_start(watch_state_p state) {
  printf("transition to start \n");
  default_impl(state);
  state->start = stop_watch;
}
