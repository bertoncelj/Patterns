#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <cmocka.h>

#include "queue.h"

#define BUFFER_SIZE 10

// Example usage:
typedef struct {
  uint8_t id;
  char name[20];
} Person;

static void test_queue_uint8_size_10_all(void **state) {
  (void)state; // unused

  // overwrite it with bummy variables
  uint8_t buffer[BUFFER_SIZE] = {99, 99, 99, 99, 99, 99, 99, 99, 99, 99};
  queue_t q;

  init_queue(&q, buffer, sizeof(uint8_t), 10);

  assert_true(is_active(&q));
  // Test when queue is empty
  assert_true(is_empty(&q));
  assert_int_equal(get_size(&q), 0);
  assert_int_equal(remaining_space(&q), (BUFFER_SIZE - 1) * sizeof(uint8_t));
  assert_false(is_full(&q));

  uint8_t val = 5;

  // Insert element into the queue
  assert_true(insert_element(&q, &val));
  assert_int_equal(remaining_space(&q),
                   (BUFFER_SIZE - 1) * sizeof(uint8_t) - 1);
  assert_false(is_empty(&q));
  assert_int_equal(get_size(&q), 1);

  uint8_t out_val;

  // Remove element from the queue
  assert_true(remove_element(&q, &out_val));
  assert_int_equal(remaining_space(&q), (BUFFER_SIZE - 1) * sizeof(uint8_t));
  assert_true(is_empty(&q));
  assert_int_equal(out_val, val);

  // Check overflow
  for (uint8_t i = 0; i < 10 - 1; i++) {
    assert_true(insert_element(&q, &i));
  }

  assert_int_equal(remaining_space(&q), 0);
  assert_true(is_full(&q));
  assert_false(insert_element(&q, &val)); // Should fail since queue is full

  // Check underflow
  for (uint8_t i = 0; i < 10 - 1; i++) {
    assert_true(remove_element(&q, &out_val));
    assert_int_equal(out_val, i);
  }

  assert_int_equal(remaining_space(&q), (BUFFER_SIZE - 1) * sizeof(uint8_t));
  assert_true(is_empty(&q));
  assert_false(
      remove_element(&q, &out_val)); // Should fail since queue is empty
}

// Test insertion and removal from the queue
static void test_queue_size_person(void **state) {
  (void)state; // unused

  Person buffer[5 * sizeof(Person)];
  queue_t queue;
  init_queue(&queue, (uint8_t *)buffer, sizeof(Person), 5);

  Person john = {1, "John"};
  Person jane = {2, "Jane"};
  Person output;

  assert_int_equal(insert_element(&queue, &john), 1); // successful insert
  assert_int_equal(insert_element(&queue, &jane), 1); // successful insert
  assert_int_equal(is_empty(&queue), 0); // queue should not be empty

  assert_int_equal(remove_element(&queue, &output), 1); // successful remove
  assert_int_equal(output.id, john.id);                 // should be John
  assert_string_equal(output.name, john.name);

  assert_int_equal(remove_element(&queue, &output), 1); // successful remove
  assert_int_equal(output.id, jane.id);                 // should be Jane
  assert_string_equal(output.name, jane.name);
}

//
// Test insertion and removal from the queue
static void test_queue_size_person_all(void **state) {
  (void)state; // unused

  uint8_t buffer[10 * sizeof(Person)];
  queue_t queue;
  init_queue(&queue, (uint8_t *)buffer, sizeof(Person), 10);

  Person persons[] = {{1, "John"},    {2, "Jane"},    {3, "Alice"},
                      {4, "Bob"},     {5, "Charlie"}, {6, "Diana"},
                      {7, "Edward"},  {8, "Fiona"},   {9, "George"},
                      {10, "Hannah"}, {11, "Ian"},    {12, "Julia"}};
  Person output;
  for (uint8_t i = 0; i < 10 - 1; i++) {
    assert_int_equal(insert_element(&queue, &persons[i]),
                     1);                   // successful insert
    assert_int_equal(is_empty(&queue), 0); // queue should not be empty
  }
  assert_int_equal(insert_element(&queue, &persons[9]), 0);
  assert_int_equal(insert_element(&queue, &persons[10]), 0);
  assert_int_equal(insert_element(&queue, &persons[11]), 0);

  for (uint8_t i = 0; i < 10 - 1; i++) {

    assert_int_equal(remove_element(&queue, &output), 1); // successful remove
    assert_int_equal(output.id, persons[i].id);           // should be John
    assert_string_equal(output.name, persons[i].name);
  }
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_queue_uint8_size_10_all),
      cmocka_unit_test(test_queue_size_person),
      cmocka_unit_test(test_queue_size_person_all),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
