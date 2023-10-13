#include "cat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat_speak() { printf("meow!\n"); }

void cat_destroy(Animal *animal) {
  AnimalCat *cat = (AnimalCat *)animal;
  free(cat);
  printf("free cat\n");
}

void cat_only() { printf("Cat only func\n"); }

Animal *animal_cat_create() {
  // assign function implementations to interface
  static const AnimalInterface vtable = {cat_speak, cat_destroy};
  static Animal base = {&vtable};
  static AnimalCat cat_construct;

  // create the AnimalCat instance
  AnimalCat *cat = &cat_construct;
  memcpy(&cat->base, &base, sizeof(base));

  // AnimalCat specific members
  cat->cat_only = cat_only;
  cat->cat_id = 1;

  return (Animal *)(&cat->base);
}
