#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dog.h"

void dog_speak() { printf("bark!\n"); }

void dog_destroy(Animal *animal) {
  AnimalDog *dog = (AnimalDog *)animal;
  free(dog);
  printf("free dog\n");
}

void dog_only() { printf("Dog only func\n"); }

Animal *animal_dog_create() {
  // assign function implementations to interface
  static const AnimalInterface vtable = {dog_speak, dog_destroy};
  static Animal base = {&vtable};
  static AnimalDog swag;
  // create the AnimalDog instance
  AnimalDog *dog = &swag;
  memcpy(&dog->base, &base, sizeof(base));

  // AnimalDog specific members
  dog->dog_only = dog_only;

  return (Animal *)(&dog->base);
}
