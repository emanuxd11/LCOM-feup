#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

int (kbd_subscribe_int)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();

int (verify_obf)(uint8_t status_reg);

int (verify_timeout)(uint8_t status_reg);

int (verify_parity)(uint8_t status_reg);

bool (is_make)(uint8_t scancode);

uint8_t (scan_n_bytes)(uint8_t scancode);

int (read_keyboard_buffer)(uint8_t *code);

int (enable_interrupts)();
