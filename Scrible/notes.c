#include <stdio.h>

#include "event.h"
#include "queue.h"
#include "time.h"

#include "input.h"
#include "output.h"

// add + 1
#define MAX_NUM_COMMANDS 10

// Global
uint8_t buffer_g[MAX_NUM_COMMANDS * sizeof(commands_t)];
queue_t queue_g;

int main() {
  // Define the event table

  srand(time(NULL));

  // init
  init_queue(&queue_g, (uint8_t *)buffer_g, sizeof(commands_t),
             MAX_NUM_COMMANDS);

  output_init();
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
