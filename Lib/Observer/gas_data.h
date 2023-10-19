#ifndef _gas_data_h_
#define _gas_data_h_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct gas_data_t gas_data_t;

struct gas_data_t {
  uint8_t N2_conc;
  uint8_t O2_conc;
  uint16_t flow_rate;
};

// Constructors and destructors
void gas_data_init(gas_data_t *const self);
void gas_data_cleanup(gas_data_t *const self);
gas_data_t *gas_data_create(void);
void gas_data_destroy(gas_data_t *const self);
#endif
