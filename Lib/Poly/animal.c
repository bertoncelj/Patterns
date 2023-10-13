#include "animal.h"

void animal_speak(Animal *animal) { animal->vtable->speak(); }

void animal_destroy(Animal *animal) { animal->vtable->destroy(animal); }
