#ifndef _dog_h_
#define _dog_h_
#include "animal.h"
typedef struct animal_dog_s {
  animal_t *base;
  // specific function
  void (*dog_only)(void);
} animal_dog_t;

animal_t *animal_create_dog();
#endif // _dog_h_
