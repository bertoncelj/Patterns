#include <stdio.h>

#include "run_state.h"
#include "stop_state.h"
#include "task.h"
#include "task_state_internal.h"

int main(void) {

  // INIT
  struct task_s ime;
  transition_to_stop(&ime.state);

  printf("Hello Task!\n");
  run_task(&ime);
  run_task(&ime);
  run_task(&ime);
  run_task(&ime);
  run_task(&ime);
  run_task(&ime);
  run_task(&ime);
  stop_task(&ime);

  return 0;
}
