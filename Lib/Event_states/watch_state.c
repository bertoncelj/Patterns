#include "watch_state.h"
#include "watch_state_internal.h"
#include <stdio.h>

static void default_stop(watch_state_p state) { printf("Default stop!\n"); }

static void default_start(watch_state_p state) { printf("Default start!\n"); }

void default_impl(watch_state_p state) {
  printf("Default impt\n");
  state->start = default_start;
  state->stop = default_stop;
}
