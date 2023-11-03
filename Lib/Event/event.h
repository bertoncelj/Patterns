#ifndef _event_h_
#define _event_h_

#include <stdint.h>
#include <stdlib.h>

#include "queue.h"

typedef enum result_e {
  EVENT_DONE = 0,
  EVENT_KILL = 1,
  EVENT_AGAIN = 2,
  EVENT_REENTRE = 3,
} event_t;

typedef enum state_s { INIT, RUNNING, SLEEP } task_state_t;

typedef enum input_s { RUN, STOP, TOGGLE, NONE, DUMMPY } input_state_t;

typedef struct commands_s {
  uint8_t name[20];
  uint8_t command[20];
  uint8_t priority;
  event_t (*event_func)(input_state_t);
  input_state_t input_state;
} commands_t;

event_t event_execute(struct commands_s *event);

void event_handler(queue_t *const queue);

#endif
