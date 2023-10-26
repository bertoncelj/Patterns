#include <stdio.h>

#include "event.h"
#include "queue.h"

#include "input.h"

// add + 1
#define MAX_NUM_COMMANDS 10

// Global
uint8_t buffer_g[MAX_NUM_COMMANDS * sizeof(commands_t)];
queue_t queue_g;

void output(void) {

  // neki neki
  printf("output\n");
  // neki neki
}

int main() {
  // Define the event table

  srand(time(NULL));
  struct commands_s event_table[20] = {
      {"led1 toggle", "<led_on_1>", 0, foo1},
      {"led2 toggle", "<led_on_2>", 0, foo2},
      {"led3 toggle", "<led_on_3>", 0, foo3},
      {"led4 toggle", "<led_on_4>", 0, foo4},
      {"led5 toggle", "<led_on_5>", 0, foo5},
  };

  // init
  init_queue(&queue_g, (uint8_t *)buffer_g, sizeof(commands_t),
             MAX_NUM_COMMANDS);

  // for (uint8_t i = 0; i < 5; i++) {
  // insert_element(&queue_g, &event_table[i]);
  // }
  uint8_t loop = 2;
  while (loop--) {
    input(&queue_g);
    event_handler(&queue_g);
    output();
  }

  return 0;
}
