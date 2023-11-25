#include <stdio.h>

#include "run_state.h"
#include "stop_state.h"
#include "task.h"
#include "task_state_internal.h"

int main(void) {
  struct task_s tasks;
  task_p tt;
  tt = &tasks;

  printf("init to stop\n!");
  transition_to_stop(&tt->state);

  stop_task(tt);
  stop_task(tt);
  run_task(tt);
  run_task(tt);

  process_task(tt);
  run_task(tt);
  run_task(tt);

  stop_task(tt);
  stop_task(tt);
  process_task(tt);
  process_task(tt);
  run_task(tt);
  stop_task(tt);

  return 0;
}
