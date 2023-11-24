#include "event_table.h"
#include "task_adc.h"
#include "task_eeprom.h"
#include "task_info.h"
#include "task_lcd.h"
#include "task_led.h"
#include "task_meas.h"
#include "task_optic.h"
#include "task_temper.h"

struct commands_s avaiable_event_table[MAX_AVAIABLE_TASK_COMMANDS] = {
    // LED
    {"descrip1", "run_led", 0, led_task, RUN},
    // {"descrip2", "tog_led", 0, led_task, TOGGLE},
    {"descrip4", "stop_led", 0, led_task, STOP},

    // ADC
    {"descrip5", "run_adc", 0, adc_task, RUN},
    {"descrip6", "stop_adc", 0, adc_task, STOP},
    // {"descrip7", "tog_adc", 0, adc_task, TOGGLE},

    // LCD
    {"descrip", "run_lcd", 0, lcd_task, RUN},
    {"descrip", "stop_lcd", 0, lcd_task, STOP},

    // INFO
    {"descrip", "info", 0, info_task, RUN},

    // MEAS
    {"descrip", "run_meas", 0, meas_task, RUN},
    {"descrip", "stop_meas", 0, meas_task, STOP},

    // Optic
    {"descrip", "run_optic", 0, optic_task, RUN},
    {"descrip", "stop_optic", 0, optic_task, STOP},

    // Optic button
    {"descrip", "run_optic_button", 0, optic_button_task, RUN},
    {"descrip", "stop_optic_button", 0, optic_button_task, STOP},

    // Temper mag
    {"descrip", "run_mag_temper", 0, mag_temper_task, RUN},
    {"descrip", "stop_mag_temper", 0, mag_temper_task, STOP},

    // Temper cover
    {"descrip", "run_cover_temper", 0, cover_temper_task, RUN},
    {"descrip", "stop_cover_temper", 0, cover_temper_task, STOP},

    // eeprom read write
    {"descrip", "write_ee", 0, ee_0_task, RUN},
    {"descrip", "read_ee", 0, ee_0_task, STOP},

};
