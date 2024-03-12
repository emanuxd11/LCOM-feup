#include "keyboard.h"

int hook_id_kbd = 1;

uint8_t scancode = 42;

bool isRead = false;

#define DELAY_US    20000

int (kbd_subscribe_int)(uint8_t *bit_no){

    if (bit_no == NULL) return -1;

    *bit_no = BIT(hook_id_kbd);

    return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_kbd);
}

int (kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id_kbd);
}

void (kbc_ih)() {
    uint8_t status_reg;

    if (util_sys_inb(STATUS_PORT, &status_reg)) return;

    if (verify_obf(status_reg)){
      int res = util_sys_inb(KBD_OUT_BUF, &scancode);
      if (verify_timeout(status_reg) && verify_parity(status_reg)){
        printf("Condition verified\n");
        if (res == 0){
          isRead = true;
          return;
        }
      }
    }
}

int (verify_obf)(uint8_t status_reg){
  return status_reg | BIT(0);
}

int (verify_timeout)(uint8_t status_reg){
  return !(status_reg | BIT(6));
}

int (verify_parity)(uint8_t status_reg){
  return !(status_reg | BIT(7));
}

bool (is_make)(uint8_t scancode){
  return (scancode & BIT(7)) == 0;
}

uint8_t (scan_n_bytes)(uint8_t scancode){
  if (scancode == 0xE0) return 2;
  return 1;
}
