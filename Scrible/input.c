#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "event_table.h"
#include "input.h"
#include "queue.h"

#define MAX_RECEIVED_DATA 100
#define MAX_COMMAND_LENGTH 100

typedef enum { OUTSIDE_COMMAND = 0, INSIDE_COMMAND } parse_state_t;

// GLOBALS
static parse_state_t parse_status_g = OUTSIDE_COMMAND;
static uint8_t command_buffer_g[MAX_COMMAND_LENGTH];
static uint8_t command_idx_g = 0;

// cmdcmp function compares two  cmd1 and cmd2.
// It returns 0 if the strings are equal, a negative value if cmd1 is less than
// cmd2, and a positive value if cmd1 is greater than cmd2.
__inline static int8_t _cmdcmp(const uint8_t *cmd1, const uint8_t *cmd2) {

  while (*cmd1 && (*cmd1 == *cmd2)) {
    cmd1++;
    cmd2++;
  }
  return *(const uint8_t *)cmd1 - *(const uint8_t *)cmd2;
}

static commands_t *find_command(uint8_t *command) {
  // Check input
  if (command == NULL)
    return NULL;

  for (uint8_t idx = 0;
       idx < sizeof(avaiable_event_table) / sizeof(avaiable_event_table[0]);
       ++idx) {

    if (_cmdcmp(command, avaiable_event_table[idx].command) == 0) {
      // command found
      return &avaiable_event_table[idx];
    }
  }

  // command not found
  return NULL;
}

void process_received_data(queue_t *que, uint8_t *data, uint8_t length) {
  commands_t *found_cmd;

  for (uint8_t i = 0; i < length; i++) {
    switch (parse_status_g) {
    case OUTSIDE_COMMAND:
      if (data[i] == '<') {
        // Command start detected, switch to INSIDE_COMMAND state
        parse_status_g = INSIDE_COMMAND;
        command_idx_g = 0;
        memset(command_buffer_g, 0, MAX_COMMAND_LENGTH); // Clear command buffer
      } // Otherwise, ignore all other characters
      break;

    case INSIDE_COMMAND:
      if (data[i] == '>') {
        // Command end detected, process the command
        if (command_idx_g > 0) { // Ensure command is not empty
          printf("Valid command: %s\n", command_buffer_g);
          found_cmd = find_command(command_buffer_g);
          if (NULL != found_cmd) {
            insert_element(que, found_cmd);
          } else {
            printf("Error: Not valid command\n");
          }

        } else {
          printf("Error: Empty command\n");
        }
        parse_status_g = OUTSIDE_COMMAND;
      } else if (data[i] == '<') {
        // New command starts before the previous one ended, reset buffer
        printf("Error: Command start detected before previous command ended\n");
        command_idx_g = 0;
        memset(command_buffer_g, 0, MAX_COMMAND_LENGTH); // Clear command buffer
      } else if (command_idx_g < MAX_COMMAND_LENGTH - 1) {
        // Add character to command buffer if there is space
        command_buffer_g[command_idx_g++] = data[i];
      } else {
        // Command buffer overflow, reset buffer and go to OUTSIDE_COMMAND state
        printf("Error: Command too long, buffer overflow\n");
        parse_status_g = OUTSIDE_COMMAND;
      }
      break;
    }
  }
}

uint8_t get_data_rx(uint8_t port, void *buff, uint8_t wanted_data) {
  static uint8_t idx = 0;
  const char *dummy_data_examples[] = {

      "<run_adc>",  "<run_led>", "<run_led>", "",
      "<stop_adc>", "",          ""
      // "<run_led><tog_led><run_led><stop_led>"
      // "<cmd1><cmd2><cmd3>",
      // "<cmd1>",
      // "<cmd4><incomplete", "complete><cmd5>",
      // "<empty><><cmd6>", "wrong><cmd7><cmd8>"
  };

  // Choose a random example
  // int example_index =
  // rand() % (sizeof(dummy_data_examples) / sizeof(dummy_data_examples[0]));

  printf("input idx: %d\n", idx);

  const char *dummy_data = dummy_data_examples[idx];
  uint8_t length = strlen(dummy_data);
  idx++;

  // If wanted_data is less than the length of dummy_data, adjust length
  if (length > wanted_data) {
    length = wanted_data;
  }

  memcpy(buff, dummy_data, length);
  return length;
}

void input(queue_t *que) {

  static int entree = 0;
  uint8_t rx_buffer[MAX_RECEIVED_DATA];

  printf("input\n");
  // if (entree == 1)
  // return;

  uint8_t received_length = get_data_rx(0, rx_buffer, MAX_RECEIVED_DATA);

  if (received_length > 0) {
    process_received_data(que, rx_buffer, received_length);
  }
  entree++;
}
