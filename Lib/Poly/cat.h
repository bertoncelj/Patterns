#ifndef CAT_H
#define CAT_H

#include "animal.h"

// First member is the base type
typedef struct AnimalCat {
  Animal *base;
  // derived type specific members
  int cat_id;
  void (*cat_only)(void);
} AnimalCat;

Animal *animal_cat_create();

#endif
