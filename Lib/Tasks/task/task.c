#include "task.h"
#include "task_state_internal.h"

struct task_s {
  struct task_state_s state;
  char *name;
  int display;
};

void run_task(task_p instance) {
  instance->state.event_run_func(&instance->state);
}

void stop_task(task_p instance) {
  instance->state.event_stop_func(&instance->state);
}
