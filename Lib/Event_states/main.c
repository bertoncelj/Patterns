#include <stdio.h>

#include "digi.h"

int main(void) {
  digi_watch_p instance = create_watch();
  printf("Here\n");

  start_watch(instance);
  start_watch(instance);
  start_watch(instance);
  start_watch(instance);
  start_watch(instance);
  stop_watch(instance);
  stop_watch(instance);
  stop_watch(instance);
  start_watch(instance);
  start_watch(instance);
  stop_watch(instance);

  printf("Hello World!\n");
  return 0;
}
