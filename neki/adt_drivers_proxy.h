#ifndef _adt_drivers_proxy_h_
#define _adt_drivers_proxy_h_

#include <stdint.h>
#include <stdlib.h>

void send_telegram_msg(uint8_t *const buff, const size_t buffsize);

void send_wired_data(uint8_t *const data, const size_t data_size);

size_t receive_wired_data(void *get_data, size_t request_size_data);

uint16_t get_RTC_time(void);

uint16_t get_optic_sensor_value(void);

uint8_t get_magnetic_temper_value(void);

uint8_t get_cover_temper_value(void);

void set_imp_led_on(void);

void set_imp_led_off(void);

void eeprom_read_data(uint8_t *data, uint16_t address, uint16_t datasize);

void eeprom_write_data(uint8_t *data, uint16_t address, uint16_t datasize);
#endif
