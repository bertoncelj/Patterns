#ifndef DOG_H
#define DOG_H

#include "animal.h"

// The first member of the derived type
// should always be the base type
typedef struct AnimalDog {
  Animal *base;
  // derived type specific members
  void (*dog_only)(void);
} AnimalDog;

Animal *animal_dog_create();

#endif
