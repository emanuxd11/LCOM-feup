#include <lcom/lcf.h>

#include "i8254.h"


int timer_hook_id = 0;


int (timer_get_conf)(unsigned char timer, unsigned char *st) {

  if (timer < 0 || timer > 2 || st == NULL) {
    return 1;
  }

  sys_outb(TIMER_CTRL, BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1));

  if (util_sys_inb(TIMER(timer), st) != 0) return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t conf, enum timer_status_field field) {

  // if (timer < 0 || timer > 2) return 1;

  // return timer_print_config();
  return 0;
}

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  if (timer < 0 || timer > 2 || freq < 19) {
    return 1;
  }

  uint8_t old_conf, new_conf;
  if (timer_get_conf(timer, &old_conf) != 0) {
    return 1;
  }

  uint8_t timer_selection = TIMER_SEL0;
  if (timer == 1) {
    timer_selection = TIMER_SEL1;
  } else if (timer == 2) {
    timer_selection = TIMER_SEL2;
  }
  new_conf = (old_conf & 0x0F) | BIT(5) | BIT(4) | timer_selection;

  uint16_t initial_val = TIMER_FREQ / freq;
  uint8_t lsb, msb;
  util_get_LSB(initial_val, &lsb);
  util_get_LSB(initial_val, &msb);

  sys_outb(TIMER_CTRL, new_conf); // avisar o timer que se vai escrever para lá uma config nova para o timer <timer> (new conf)
  // escrever para o timer <timer> a nova configuração 8 bits de cada vez
  sys_outb(TIMER(timer), lsb);
  sys_outb(TIMER(timer), msb);

  return 0;
}

void (timer_int_handler)() {

  return;
}

int (timer_subscribe_int)(uint8_t *bit_no) {

  if (bit_no == NULL) {
    return 1;
  }

  *bit_no = BIT(timer_hook_id);

  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id);
}

int (timer_unsubscribe_int)() {

  return sys_irqrmpolicy(&timer_hook_id);
}
