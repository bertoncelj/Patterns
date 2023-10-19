#include "gas_data.h"

void gas_data_init(gas_data_t *const self) { (void)self; } // not used
//
//
//

void gas_data_cleanup(gas_data_t *const self);

gas_data_t *gas_data_create(void) {
  gas_data_t *self = (gas_data_t *)malloc(sizeof(gas_data_t));
  if (self != NULL)
    gas_data_init(self);
  return self;
}

void gas_data_destroy(gas_data_t *const self) {

  if (self != NULL) {
    gas_data_cleanup(self);
  }
  free(self);
}
