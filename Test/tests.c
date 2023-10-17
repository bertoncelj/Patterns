#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <cmocka.h>

#include "queue.h"

void print_buff(uint8_t *buff) {
  for (uint8_t i = 0; i < 10; i++) {
    printf("%d ", buff[i]);
  }
  printf("\n");
}
static void test_insert_remove(void **state) {
  (void)state; // unused

  uint8_t buffer[10] = {99, 99, 99, 99, 99, 99, 99, 99, 99, 99};
  queue_t q;

  init_queue(&q, buffer, sizeof(uint8_t), 10);

  assert_true(is_active(&q));
  print_buff(buffer);
  // Test when queue is empty
  assert_true(is_empty(&q));
  assert_int_equal(get_size(&q), 0);
  assert_false(is_full(&q));
  printf("here\n");

  uint8_t val = 5;

  print_buff(buffer);
  // Insert element into the queue
  assert_true(insert_element(&q, &val));
  print_buff(buffer);
  assert_false(is_empty(&q));
  assert_int_equal(get_size(&q), 1);

  uint8_t out_val;

  // Remove element from the queue
  printf("HAAAAAAAAAAAAAAAAA\n");
  print_buff(buffer);
  assert_true(remove_element(&q, &out_val));
  print_buff(buffer);
  assert_true(is_empty(&q));
  assert_int_equal(out_val, val);

  // Check overflow
  for (uint8_t i = 0; i < 10 - 1; i++) {
    printf("III: %d\n", i);
    assert_true(insert_element(&q, &i));
    print_buff(buffer);
  }

  printf("ANNNNNNNNNNNNAAAAAAAAAAAA\n");
  printf("self->head: %zu\n", q.head);
  printf("self->item_size: %zu\n", q.item_size);
  printf("self->capacity: %zu\n", q.capacity);
  printf("self->tail: %zu\n", q.tail);
  printf("self->size: %zu\n", q.size);
  printf("yolo\n");
  assert_true(is_full(&q));
  printf("yolo\n");
  assert_false(insert_element(&q, &val)); // Should fail since queue is full

  // Check underflow
  for (uint8_t i = 0; i < 10 - 1; i++) {
    assert_true(remove_element(&q, &out_val));
    assert_int_equal(out_val, i);
  }

  assert_true(is_empty(&q));
  assert_false(
      remove_element(&q, &out_val)); // Should fail since queue is empty
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_insert_remove),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
