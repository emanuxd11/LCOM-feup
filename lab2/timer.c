#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  if (timer < 0 || timer > 2) return -1;

  uint8_t current_configuration;

  timer_get_conf(timer, &current_configuration);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  if (timer < 0 || timer > 2 || st == NULL){
    return -1;
  }

  uint8_t command = BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1);

  if (sys_outb(TIMER_CTRL, command) != 0) return -1;

  if (util_sys_inb(TIMER(timer), st) != 0) return -1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  if (timer < 0 || timer > 2) return -1;

  union timer_status_field_val value;

  switch(field){
    case tsf_all:
      value.byte = st;
      break;
    case tsf_initial:{
      uint8_t bits = (st & (BIT(4) | BIT(5))) >> 4;
      value.in_mode = bits;
      break;
    }
    case tsf_mode:{
        uint8_t bits = (st & (BIT(1) | BIT(2) | BIT(3))) >> 1;
        if (bits >= 6){
          value.count_mode = bits - 4;
        }
        else{
          value.count_mode = bits;
        }
        break;
      }
    case tsf_base:
      value.bcd = st & BIT(0);
      break;
    default:
      break;
  }

  return timer_print_config(timer, field, value);

}
