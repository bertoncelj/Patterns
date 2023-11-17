#include <stdio.h>

#include "task_state.h"

static void default_stop(task_state_p state) {
  // unused prameter
  (void)state;
  printf("dafault run\n");
}

static void default_run(task_state_p state) {
  // unused prameter
  (void)state;
  printf("dafault run\n");
}

void default_impl(task_state_p state) {
  state->event_run_func = default_run;
  state->event_stop_func = default_stop;
}
