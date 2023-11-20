#include <stdio.h>

#include "task.h"
#include "task_state_internal.h"

void run_task(task_p instance) {
  printf("in run_task\n");
  instance->state.event_run_func(&instance->state);
}

void stop_task(task_p instance) {
  printf("in stop_task\n");
  instance->state.event_stop_func(&instance->state);
}

void process_task(task_p instance) {
  instance->state.event_process_func(&instance->state);
}
