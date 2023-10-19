#ifndef _gas_sensor_h_
#define _gas_sensor_h_

#include "gas_sensor.h"

/* the function pointer type

The first value of the function pointer is to the instance

data of the class. The second is a ptr to the new gas data

*/

typedef void (*gas_dat_acceptor_prt)(void *, struct gas_data_t *)

#endif
