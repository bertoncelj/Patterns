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

typedef struct commands_s {
  uint8_t name[20];
  uint8_t command[20];
  uint8_t priority;
  event_t (*event_func)(void);
} commands_t;

event_t foo1();
event_t foo2();
event_t foo3();
event_t foo4();
event_t foo5();

event_t event_execute(struct commands_s *event);

void event_handler(queue_t *const queue);

#endif
