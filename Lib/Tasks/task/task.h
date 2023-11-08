#ifndef _task_h_
#define _task_h_

typedef struct task_s *task_p;

void run_task(task_p instance);

void stop_task(task_p instance);

#endif
