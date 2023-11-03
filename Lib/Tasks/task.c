#include "task.h"

void start_task();
void stop_task();
void init_task();
//
// event_t task(task_state state) {
//   switch (state) {
//   case SLEEP:
//     stop_task();
//     break;
//
//   case RUNNING:
//     start_task();
//     break;
//   }
//   return EVENT_DONE;
// }
//
// event_t task_1(void) {
//   // Blink led 0
//   return EVENT_DONE;
// }
