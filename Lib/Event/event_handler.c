#include "event.h"
#include "queue.h"

void led_on(void);

struct commands_s event_table[20] =

    {
        {"led1 toggle", "<led_on_1>", 0, led_on},
        {"led1 toggle", "<led_on_1>", 0, led_on},
};

void event_init();
