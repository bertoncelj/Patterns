#include "output.h"
#include "queue.h"

#define OUTPUT_BUFF_SIZE 100

queue_t que_out;
uint8_t out_que_buff_g[OUTPUT_BUFF_SIZE];
uint8_t out_buff_g[OUTPUT_BUFF_SIZE];

void output_init(void) {
  // init
  init_queue(&que_out, (uint8_t *)out_que_buff_g, sizeof(uint8_t),
             OUTPUT_BUFF_SIZE);
}

int8_t output_print(uint8_t *const data, size_t data_size) {
  uint8_t debug = 0;
  for (size_t idx = 0; idx < data_size; idx++) {

    if (!insert_element(&que_out, (data + idx))) {
      debug++;
      // ERROR buffer full
      return 0;
    }
  }

  return debug;
}

uint16_t output_dump(uint8_t *data) {
  size_t filed_bytes = 0;
  uint16_t idx = 0;

  filed_bytes = que_out.size;
  while (que_out.size != 0) {
    remove_element(&que_out, (data + idx));
    idx++;
  }

  return filed_bytes;
}

void uart_tx(int port, uint8_t *buffer, size_t size) {
  // unused args
  (void)port;

  if (!buffer) {
    printf("Error: Buffer is NULL\n");
    return;
  }

  fflush(stdout);
  for (size_t i = 0; i < size; ++i) {
    // Here you would actually send the data to the UART port.
    // For this example, we just print the character to simulate UART
    // transmission.
    putchar(buffer[i]);
  }
  putchar('\n'); // Just to make the output more readable
  fflush(stdout);
}

void output(void) {
  printf("OUTPUT!\n");
  uint16_t output_size;
  output_size = output_dump(out_buff_g);
  printf("output size %d \n", output_size);
  if (output_size > 0) {
    uart_tx(0 /*port*/, (uint8_t *)out_buff_g, output_size);
  }
}
