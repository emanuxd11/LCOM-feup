#include "rtclock.h"


int (rtc_get_out)(uint8_t value_idx, uint8_t *output) {
  if (sys_outb(RTC_ADDR_REG, value_idx) != 0) {
    return 1;
  } 

  if (util_sys_inb(RTC_DATA_REG, output) != 0) {
    return 1;
  }

  return 0;
}

int (rtc_write)(uint8_t data) {
  return 1;
}

int (rtc_read_time)() {
  uint8_t seconds, minutes, hours;

  if (rtc_get_out(RTC_SECONDS, &seconds) != 0) {
    return 1;
  }

  if (rtc_get_out(RTC_MINUTES, &minutes) != 0) {
    return 1;
  }

  if (rtc_get_out(RTC_HOURS, &hours) != 0) {
    return 1;
  }

  printf("SECONDS: %d, MINUTES: %d, HOURS: %d", seconds, minutes, hours);

  return 0;
}
