#ifndef ANIMAL_H
#define ANIMAL_H

typedef struct Animal_s {
  const struct AnimalInterface *const vtable;
} Animal;

// function pointers that needs to
// be implemented by the derived type
typedef struct AnimalInterface {
  void (*speak)();
  void (*destroy)(Animal *);
} AnimalInterface;

// functions for interacting with the
// instances
void animal_speak(Animal *animal);
void animal_destroy(Animal *animal);
#endif
