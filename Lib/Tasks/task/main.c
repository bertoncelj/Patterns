#include <stdio.h>

#include "stop_state.h"
#include "task.h"
#include "task_state_internal.h"

int main(void) {

  task_state_p new_task;
  transition_to_stop(&new_task->state);
  printf("Hello Task!\n");

  return 0;
}
