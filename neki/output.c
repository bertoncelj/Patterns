#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "output.h"
#include "queue.h"

#include "adt_drivers_proxy.h"

#define OUTPUT_BUFF_SIZE 100

queue_t que_out;
uint8_t out_que_buff_g[OUTPUT_BUFF_SIZE];
uint8_t out_buff_g[OUTPUT_BUFF_SIZE];

// TODO: Replace Delay
//////////////////// QUICK FIX /////////////////////////
#define CPU_FREQUENCY_HZ 48000000 // 48 MHz

// Delays microseconds
void delay_us(uint32_t microseconds) {
  uint32_t loop_count = (CPU_FREQUENCY_HZ / 1000000) * microseconds;

  volatile uint32_t i;
  for (i = 0; i < loop_count; i++) {
    __asm__("NOP");
  }
}

// Delays milliseconds
void delay_ms(uint32_t milliseconds) {
  while (milliseconds > 0) {
    delay_us(1000);
    milliseconds--;
  }
}

//////////////////////////////////////////////////////////
///

void print_all_commands(queue_t *self, commands_t *item_to_seacrh[]) {
  commands_t *help_item = NULL;
  const char *output_msg = "output:\n";
  const char *output1_msg = "endput\n";

  if (is_empty(self))
    return;

  output_print((uint8_t *)output_msg, strlen(output_msg));

  for (uint8_t idx = 0; idx < self->size; idx++) {

    if (peek_element(self, idx, help_item)) {
      print_command(help_item);
    }
  }
  output_print((uint8_t *)output1_msg, strlen(output1_msg));
}

void print_command(const commands_t *self) {
  // output_print("->", 2);
  output_print((uint8_t *)self->command, 20);
  // output_print('\n', 1);
}

void output_init(void) {
  // init
  init_queue(&que_out, (uint8_t *)out_que_buff_g, sizeof(uint8_t),
             OUTPUT_BUFF_SIZE);
}

size_t transform_uint_to_ascii_hex(const void *in_num, size_t num_size,
                                   uint8_t *out_ascii) {
  uint8_t acc;
  uint32_t data = 0;

  // copy number to data
  memcpy(&data, in_num, num_size);

  for (uint8_t i = num_size * 2; i != 0; --i) {
    // get byte number value into accumulator
    acc = (data >> (4 * (i - 1))) & 0x0F;

    if (acc <= 9) {
      // number 0 .. 9
      acc = acc + 0x30;
    } else {
      // letters A,B,C,D,E,F
      acc = acc + 0x57;
    }
    // save into out_ascii array
    out_ascii[(num_size * 2) - i] = (uint8_t)acc;
  }

  // end with null terminator
  out_ascii[num_size * 2] = '\0';

  return num_size + 1;
}

int8_t output_print(uint8_t *const data, size_t data_size) {

  size_t rez = insert_bytes(&que_out, data, data_size);
  if (rez != data_size) {
    // ERROR buffer full
    return 0;
  }
  return rez;
}

uint16_t output_dump(uint8_t *data) {
  size_t filed_bytes = 0;

  // get items in output
  filed_bytes = que_out.size;

  return remove_bytes(&que_out, data, filed_bytes);
}

void output(void) {
  uint16_t output_size;

  output_size = output_dump(out_buff_g);

  /* Sends data out */
  if (output_size > 0) {
    send_wired_data((uint8_t *)out_buff_g, output_size);

    /* TODO: Dummy delay to allow UART RX for send all data */
    // delay_ms(1);
    delay_us(1000);
  }
}
