#include "event_table.h"
#include "task_led.h"

struct commands_s avaiable_event_table[20] = {
    {"descrip1", "run_led", 0, led_task, RUN},
    {"descrip2", "tog_led", 0, led_task, TOGGLE},
    {"descrip3", "run_led", 0, led_task, RUN},
    {"descrip4", "stop_led", 0, led_task, STOP}
    // {"description2", "cmd2", 0, foo2},
    // {"description3", "cmd3", 0, foo3},
    // {"description4", "cmd4", 0, foo4},
    // {"description5", "cmd5", 0, foo5},
};
