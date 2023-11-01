#include <stdio.h>
#include <stdlib.h>


#include "digi.h"
#include "watch_state.h"
#include "watch_state_internal.h"

// str
// {
//   watch_state state;
//   int time;
// };

struct digi_watch
{
  int time;
  struct watch_state state;
};

digi_watch_p create_watch(void)
{
  digi_watch_p instance = malloc(sizeof( *instance));
  
  if(NULL != instance)
  {
    transition_to_start(&instance->state);
  }
  return instance;
}

void destroy_watch(digi_watch_p instance)
{
  free(instance);
}

void start_watch(digi_watch_p instance)
{
  printf("digi start\n");
  instance->state.start(&instance->state);
}


void stop_watch(digi_watch_p instance)
{

  printf("digi stop\n");
  instance->state.stop(&instance->state);
}
