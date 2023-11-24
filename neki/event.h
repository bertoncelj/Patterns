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

typedef enum input_s { RUN, STOP, TOGGLE, NONE } input_state_t;

typedef struct commands_s {
  uint8_t name[20];
  uint8_t command[20];
  uint8_t priority;
  event_t (*event_func)(input_state_t);
  input_state_t input_state;
} commands_t;

// event_t event_execute(struct commands_s *event);
//
void event_init(void);

int8_t event_insert(const commands_t *element);

int8_t event_remove(commands_t *element);

commands_t *event_find_command(const uint8_t *search_command,
                               commands_t *result_cmd,
                               const size_t command_length);

void event_handler(void);

#endif
