#include <stdio.h>

#include "queue.h"
#include "sensor.h"

#include "animal.h"
#include "dog.h"

int main_1(void) {
  sensor_t sens_0;
  sensor_create(&sens_0, 10, 22, 123, 0);

  print_sensor(&sens_0);
  set_value(&sens_0, 99);
  printf("New value %d ", get_value(&sens_0));
  printf("End of program\n");

  queue_t arr;
  init_queue(&arr, is_full_cb, is_empty_cb, get_size_cb, insert_element_cb,
             remove_element_cb);

  printf("is full %d\n", arr.is_full(&arr));
  if (arr.is_full(&arr)) {
  }
  for (int i = 0; i < 9; i++) {
    insert_element_cb(&arr, i + 1);
    printf("Get size %d\n", get_size_cb(&arr));
    print_all_elements_cb(&arr);
  }
  for (int i = 0; i < 9; i++) {
    remove_element_cb(&arr);
    printf("Get size %d\n", get_size_cb(&arr));
    print_all_elements_cb(&arr);
  }

  return 0;
}

int main(int argc, char **args) {
  Animal *dog = animal_dog_create();

  animal_speak(dog); // bark!

  // dog specific
  ((AnimalDog *)dog)->dog_only();

  // cat specific

  animal_destroy(dog);
  return 0;
}
