#ifndef _watch_state_internal_h_
#define _watch_state_internal_h_

typedef struct watch_state *watch_state_p;

typedef void (*event_start_func)(watch_state_p);
typedef void (*event_stop_func)(watch_state_p);

struct watch_state {
  event_start_func start;
  event_stop_func stop;
};

#endif
