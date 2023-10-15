#include <stdio.h>

#include "animal.h"
#include "cat.h"
#include "dog.h"
#include "queue.h"
#include "sensor.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Example usage:
typedef struct {
  int id;
  char name[20];
} Person;

void cb_print(const queue_t *cb) {
  printf("Circular Buffer Contents:\n");
  int byte_pos = cb->tail;
  for (int i = 0; i < (int)cb->size; i++) {
    Person *p = (Person *)(&cb->buffer[byte_pos]);
    printf("ID: %d, Name: %s\n", p->id, p->name);

    byte_pos = (byte_pos + cb->item_size) % (cb->capacity * cb->item_size);
  }
}

int main(void) {
  queue_t que;
  // Person persons[10] = {{1, "John"}, {2, "Jane"}, {3, "Doe"}};
  Person persons[10] = {};

  Person neki = {4, "hoe"};
  Person neki1 = {5, "moe"};
  printf("persons: %d", sizeof(persons));
  printf("Person: %d", sizeof(Person));
  init_queue(&que, (uint8_t *)persons, sizeof(Person),
             sizeof(persons) / sizeof(Person));
  insert_element(&que, &neki);
  cb_print(&que);
  insert_element(&que, &neki1);
  cb_print(&que);

  for (int i = 0; i < 10; i++) {
    if (!insert_element(&que, &neki1))
      printf("Failed!\n");
    cb_print(&que);
  }
  Person yolo;
  for (int i = 0; i < 10; i++) {
    if (!remove_element(&que, &yolo))
      printf("Failed!\n");
    cb_print(&que);
  }
  // remove_element();
  return 0;
}
