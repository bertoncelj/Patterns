#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <cmocka.h>

static void test_me(void **state) {
  (void)state; // unused
}

int main(void) {
  const struct CMUnitTest tests[] = {
      // item queue
      cmocka_unit_test(test_me),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
