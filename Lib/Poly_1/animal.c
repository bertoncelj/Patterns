#include "animal.h"

void animal_speak(animal_t *animal) { animal->vtable->speak(); }

void animal_kill(animal_t *animal) { animal->vtable->kill(animal); }
