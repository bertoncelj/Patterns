#ifndef _task_state_internal_h_
#define _task_state_internal_h_

// Incomplete type for state representation itself
typedef struct task_state_s *task_state_p;

typedef void (*event_run_func)(task_state_p);
typedef void (*event_stop_func)(task_state_p);

// struct task_state_s {
// event_run_func start;
// event_stop_func stop;
// };

struct task_state_s {
  void (*event_run_func)(task_state_p);
  void (*event_stop_func)(task_state_p);
};

#endif
