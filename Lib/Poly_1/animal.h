#ifndef _animal_h_
#define _animal_h_

typedef struct animal_s animal_t;
// function pointers that needs to be implemented by the derived type
typedef struct animal_interface_s {
  void (*speak)();
  void (*kill)(animal_t *);

} animal_interface_t;

typedef struct animal_s {
  const struct animal_interface *const vtable;
} animal_t;

// function for interacting with the instances
void animal_speak(animal_t *animal);
void animal_kill(animal_t *animal);

animal_t *animal_create_dog();

#endif // _animal_h_
