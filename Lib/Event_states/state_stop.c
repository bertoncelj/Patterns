#include "state_stop.h"
#include "watch_state_internal.h"  

#include "state_start.h"


static void start_watch(watch_state_p state)
{
  printf("stop watch! \n");
  transition_to_start(state);
}

void transition_to_stop(watch_state_p state)
{

  printf("transition to stop \n");
  default_impl(state);
  state->start = start_watch;
}
