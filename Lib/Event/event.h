#ifndef _event_h_
#define _event_h_

#include <stdint.h>
#include <stdlib.h>

struct commands_s {
  char name[20];
  char comman[20];
  uint8_t priority;
  void (*even_func)(void);
};

#endif
