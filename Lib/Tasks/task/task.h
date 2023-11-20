#ifndef _task_h_
#define _task_h_

#include "task_state_internal.h"

typedef struct task_s *task_p;

struct task_s {
  struct task_state_s state;
  char *name;
  int display;
};

void run_task(task_p instance);

void stop_task(task_p instance);

void process_task(task_p instance);

#endif
