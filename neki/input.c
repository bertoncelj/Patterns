#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "output.h"
#include "queue.h"

#include "event.h"

#include "adt_drivers_proxy.h"

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

void process_received_data(uint8_t *data, uint8_t length) {
  commands_t *found_cmd = NULL;
  uint8_t debug = 0;
  uint8_t result = 0;

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
          found_cmd =
              event_find_command(command_buffer_g, found_cmd, command_idx_g);
          if (found_cmd != NULL) {

            // print_command(found_cmd);
            event_insert(found_cmd);
          } else {
          }

        } else {
        }
        parse_status_g = OUTSIDE_COMMAND;
      } else if (data[i] == '<') {
        // New command starts before the previous one ended, reset buffer
        command_idx_g = 0;
        memset(command_buffer_g, 0, MAX_COMMAND_LENGTH); // Clear command buffer
      } else if (command_idx_g < MAX_COMMAND_LENGTH - 1) {
        // Add character to command buffer if there is space
        command_buffer_g[command_idx_g++] = data[i];
      } else {
        // Command buffer overflow, reset buffer and go to OUTSIDE_COMMAND state
        parse_status_g = OUTSIDE_COMMAND;
      }
      break;
    }
  }
}

void input(void) {
  uint8_t rx_buffer[MAX_RECEIVED_DATA];
  uint8_t received_length;

  received_length = receive_wired_data(rx_buffer, MAX_RECEIVED_DATA);

  /* gets some data from UART */
  if (received_length > 0) {
    process_received_data(rx_buffer, received_length);
  }
}
