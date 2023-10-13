#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dog.h"

void dog_speak() { printf("how how\n"); }

void dog_only() { printf("dog only function\n"); }

void dog_kill() { printf("dog killed! \n"); }

animal_t *animal_create_dog() {
  static const animal_interface_t vtable = {dog_speak, dog_kill};
  static animal_t base = {&vtable};

  // create the AnimalDog instance
  animal_dog_t *dog = malloc(sizeof(*dog));
  memcpy(&dog->base, &base, sizeof(base));

  dog->dog_only = dog_only;

  return (animal_t *)(&dog->base);
}
