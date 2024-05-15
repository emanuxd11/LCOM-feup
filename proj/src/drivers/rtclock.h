#ifndef _RTCLOCK_H_
#define _RTCLOCK_H_

#include <lcom/lcf.h>

#include "utils.h"

#include "../models/Datetime.h"


#define RTC_IRQ 8
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define RTC_SECONDS 0
#define RTC_MINUTES 2
#define RTC_HOURS 4
#define RTC_WEEKDAY 6
#define RTC_MONTHDAY 7
#define RTC_MONTH 8
#define RTC_YEAR 9


int (rtc_get_out)(uint8_t value_idx, uint8_t *output);
int (rtc_write)(uint8_t data);
Datetime (rtc_read_datetime)();

#endif
