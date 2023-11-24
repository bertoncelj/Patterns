#include "task.h"

event_t task_handler(input_state_t input_state, task_state_t task_state,
                     task_func_t *task_func) {
  event_t event_return;

  /* Task Handler */
  // TODO: move it to state table machine
  switch (input_state) {
  case NONE:
    switch (task_state) {
    case INIT:
      event_return = task_func->init_task();
      break;

    case RUNNING:
      event_return = task_func->run_task();
      break;

    case SLEEP:
      event_return = task_func->stop_task();
      break;
    }
    break;

  case RUN:
    switch (task_state) {
    case INIT:
      event_return = task_func->init_task();
      break;

    case RUNNING:
      event_return = task_func->run_task();
      break;

    case SLEEP:
      event_return = task_func->run_task();
      break;
    }
    break;

  case STOP:
    switch (task_state) {
    case INIT:
      // ERROR: task is not RUNNING, need to INIT FIRST
      event_return = task_func->init_task();
      break;

    case RUNNING:
      event_return = task_func->stop_task();
      break;

    case SLEEP:
      // ALREADY KILLED:
      // TODO: maybe error
      event_return = task_func->stop_task();
      break;
    }
    break;
  case TOGGLE:
    switch (task_state) {
    case INIT:
      event_return = task_func->init_task();
      break;

    case RUNNING:
      event_return = task_func->stop_task();
      break;

    case SLEEP:
      event_return = task_func->run_task();
      break;

      break;
    }
    break;

  default:
    event_return = EVENT_DONE;
    break;
  }
  return event_return;
}
