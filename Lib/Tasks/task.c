#include "task.h"

// event_t default_init(void);
// event_t default_start(void);
// event_t default_stop(void);
// event_t default_error(void);

// task_state_t task_state_led = INIT;

// task_func_t task_func = {.init_task = default_init,
// .run_task = default_start,
// .stop_task = default_stop,
// .error_task = default_error};

// state_action_t state_table[INPUT_MAX][STATE_MAX];

const state_action_prototype_t prototype_table[INPUT_MAX][3] = {

    // Actions for RUN input
    {
        {INIT, INIT_FUNC}, // init first try
        {RUNNING, START_FUNC},
        {SLEEP, STOP_FUNC} // comment
    },
    // Actions for STOP input
    {
        {INIT, INIT_FUNC}, // Error, so init
        {RUNNING, STOP_FUNC},
        {SLEEP, START_FUNC} // Already off
    },
    // Actions for TOGGLE input
    {
        {INIT, INIT_FUNC}, // neki nke
        {RUNNING, STOP_FUNC},
        {SLEEP, START_FUNC} // neki neki
    },
    // Actions for NONE input
    {
        {INIT, INIT_FUNC}, // comment
        {RUNNING, START_FUNC},
        {SLEEP, STOP_FUNC} // comment
    }

};
// Function to get the action function based on the prototype
event_t (*get_action_function(task_func_t *funcs, proto_func_t proto))(void) {
  switch (proto) {
  case INIT_FUNC:
    return funcs->init_task;
  case START_FUNC:
    return funcs->run_task;
  case STOP_FUNC:
    return funcs->stop_task;
  case ERROR_FUNC:
    return funcs->error_task;
  default:
    return NULL;
  }
}

// Initialize the state table from the prototype
void initialize_state_table(task_func_t *funcs, state_action_t **state_table) {
  for (uint8_t input = 0; input < INPUT_MAX; ++input) {
    for (uint8_t state = 0; state < STATE_MAX; ++state) {
      proto_func_t proto = prototype_table[input][state].proto;
      printf("proto %d\n", proto);
      state_table[input][state].next_state =
          prototype_table[input][state].state;
      state_table[input][state].action_func = get_action_function(funcs, proto);
    }
  }
}

void print_state_table(state_action_t **state_table) {
  printf("State Table:\n");
  for (int i = 0; i < INPUT_MAX; i++) {
    for (int j = 0; j < STATE_MAX; j++) {
      printf("Input %d, State %d: Action Func Ptr: %p\n", i, j,
             (void *)state_table[i][j].action_func);
    }
  }
}

event_t task_handler(state_action_t **state_table, input_state_t input_state,
                     task_state_t task_state_led) {
  if (input_state < 0 || input_state >= INPUT_MAX || task_state_led < 0 ||
      task_state_led > SLEEP) {
    // TODO: MUST BE ERROR
    return EVENT_DONE;
  }
  char *state_s[] = {"INIT", "RUNNING", "SLEEP"};

  char *input_s[] = {"RUN", "STOP", "TOGGLE", "NONE"};

  printf("TASK: input: %s task_state: %s \n", input_s[input_state],
         state_s[task_state_led]);
  // Retrieve the action function based on the input state and current task
  // state
  state_action_t action = state_table[input_state][task_state_led];

  // Call the action function if it's valid
  if (action.action_func) {
    return action.action_func();
  }

  // TODO: MUST BE ERROR
  return EVENT_DONE;
}
