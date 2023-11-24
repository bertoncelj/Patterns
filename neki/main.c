#include "FLASH.h"
#include "GPIO.h"
#include "RA2A2_ADC.h"
#include "RA2A2_dtc.h"
#include "RA2A2_timer.h"
#include "RTC.h"
#include "UART.h"
#include "console.h"
#include "eeprom.h"
#include "hardware_init.h"
#include "platform.h"

#include "adt.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define SAMPLE_MAX_ENTRIES (512)
#define HDLC_CONTROL_BUFFER_SIZE 48

#define INTERNAL_CLOCK (BSP_CLOCKS_SOURCE_CLOCK_HOCO)
#define EXTERNAL_32kHz_QUARTZ (BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK)

#define DATAFLASH_WRITE_BASE_ADDR (0xFE000000U)
/*******************************************************************************
 * Variables
 ******************************************************************************/

int main(void) {
  hardware_init();
  /*Setupamo da lahko prvič pademo v pravilen if()*/

  /*Enable 1s RTC output */
  rtc_set_quartz_pulses();

  /*Enable CLKOUT*/
  CLKOUT_enable(EXTERNAL_32kHz_QUARTZ);

  /* Start ADT */

  /*Testiranje LCDja part 2*/

  // gpio_pin_write(PORT4, PIN3, LEVEL_HIGH);
  adt();
}
