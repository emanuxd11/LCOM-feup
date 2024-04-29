#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

int kbc_restore_mouse();

int issue_cmd_to_mouse(uint8_t cmd);

int read_data_from_KBC_mouse(uint8_t *data);

int read_byte_to_mouse_packet();

void array_to_packet();