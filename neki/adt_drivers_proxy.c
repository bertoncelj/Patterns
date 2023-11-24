#include "adt_drivers_proxy.h"

#include "RA2A2_uart.h"
#include "UART.h"

#include "ADC12.h"
#include "GPIO.h"
#include "RTC.h"
#include "eeprom.h"

void send_telegram_msg(uint8_t *const buff, const size_t buffsize) {
  uart_tx(UART3, (uint8_t *)buff, buffsize);
}

void send_wired_data(uint8_t *const data, const size_t data_size) {
  uart_tx(UART9 /*port*/, (uint8_t *)data, data_size);
}

size_t receive_wired_data(void *get_data, size_t request_size_data) {
  return RA2A2_uart_rx(UART9, get_data, request_size_data);
}

uint16_t get_RTC_time(void) { return rtc_uptime(); }

uint16_t get_optic_sensor_value(void) {
  return console_iluminating_power_get();
}

uint8_t get_magnetic_temper_value(void) {
  // new line
  return gpio_pin_read(4, 1);
}

void set_imp_led_on(void) {
  // new line
  gpio_pin_write(4, 2, LEVEL_LOW);
}

void set_imp_led_off(void) {
  // new line
  gpio_pin_write(4, 2, LEVEL_HIGH);
}

uint8_t get_cover_temper_value(void) {
  // new line
  return gpio_pin_read(4, 0);
}

void eeprom_read_data(uint8_t *data, uint16_t address, uint16_t datasize) {
  ee24xx_read_data(data, address, datasize);
}

void eeprom_write_data(uint8_t *data, uint16_t address, uint16_t datasize) {
  ee24xx_write_data(data, address, datasize);
}
