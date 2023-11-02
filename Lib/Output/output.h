#ifndef _output_h_
#define _output_h_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void output_init(void);

int8_t output_print(uint8_t *const data, size_t data_size);

uint16_t output_dump(uint8_t *data);

void output(void);

#endif
