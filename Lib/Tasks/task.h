#ifndef _task_h_
#define _task_h_

#include "event.h"
#include <stdio.h>

#include "event.h"

// Driver actions structure
typedef struct task_func_s {
  event_t (*init_task)(void);
  event_t (*run_task)(void);
  event_t (*stop_task)(void);
  event_t (*error_task)(void);
} task_func_t;

typedef struct {
  task_state_t next_state;
  event_t (*action_func)(void);
} state_action_t;

// Function pointer type for task action functions
typedef event_t (*task_action_func)(void);

void initialize_state_table(task_func_t *funcs, state_action_t **state_table);

event_t task_handler(input_state_t input_state, task_state_t task_state,
                     task_func_t *task_func);

void print_state_table(state_action_t **state_table);

#endif /* _task_h_ */
