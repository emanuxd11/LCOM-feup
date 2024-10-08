#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

int (verify_obf)(uint8_t status_reg);

int (verify_timeout)(uint8_t status_reg);

int (verify_parity)(uint8_t status_reg);

int (configure_mouse)(uint8_t command);

int (verify_is_mouse)(uint8_t status_reg);

int (mouse_disable_data_reporting)();

bool (verify_is_first_byte)(uint8_t byte);

int (get_all_values)(uint8_t x1, uint8_t *packet);

int (parse_packet)(uint8_t *packet, struct packet* pp);
