#ifndef _sensor_h_
#define _sensor_h_

#define WRITE_ADDR 0x1111
#define WRITE_MASK 0x2222
#define READ_ADDR 0x3333
#define SENSOR_PORT 0x4444

typedef enum _interfaceType {
  MEMORY_MAPPED,
  PORT_MAPPED,
  MAPPED_MAX
} interfaceType;

typedef enum _result_s { OK, ERROR } result_t;

// Class sensor
typedef struct sensor_s {
  int filter_freq;
  int update_freq;
  int value;
  int what_kind_of_interface;
} sensor_t;

sensor_t *sensor_create(sensor_t *sens, int filter, int update, int value,
                        int what_kind_of_interface);
result_t sensor_destroy(sensor_t *sens);

int get_filter_freq(const sensor_t *const self);

int get_update_freq(const sensor_t *const self);

int get_value(const sensor_t *const self);

void set_value(sensor_t *const self, int new_value);

int get_what_king_of_interface(const sensor_t *const self);

int acquire_vlaue(sensor_t *self);

void print_sensor(sensor_t *self);

#endif /* _sensor_h_ */
