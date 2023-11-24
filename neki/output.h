#ifndef _output_h_
#define _output_h_

#include "event.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_all_commands(queue_t *self, commands_t *item_to_seacrh[]);

void print_command(const commands_t *self);

void output_init(void);

int8_t output_print(uint8_t *const data, size_t data_size);

uint16_t output_dump(uint8_t *data);

void output(void);

size_t transform_uint_to_ascii_hex(const void *in_num, size_t num_size,
                                   uint8_t *out_ascii);
#endif
