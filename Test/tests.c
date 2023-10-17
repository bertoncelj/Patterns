#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <cmocka.h>

#include "queue.h"

#define BUFFER_SIZE 10

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

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_queue_uint8_size_10_all),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
