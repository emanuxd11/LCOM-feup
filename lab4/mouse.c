#include "mouse.h"

#define BIT(n) (1 << (n))

int hook_id_mouse = 2;
uint8_t scancode;


int (mouse_subscribe_int)(uint8_t *bit_no){

    if (bit_no == NULL) return -1;

    *bit_no = BIT(hook_id_mouse);

    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse);
}

int (mouse_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id_mouse);
}

void (mouse_ih)(){
    uint8_t status_reg;

    if (util_sys_inb(STATUS_PORT, &status_reg)) return;

    if (verify_obf(status_reg)){
      util_sys_inb(KBD_OUT_BUF, &scancode);
      if (verify_timeout(status_reg) && verify_parity(status_reg) && verify_is_mouse(status_reg)){
      }
    }
}

bool (verify_is_first_byte)(uint8_t byte){
  return byte & BIT(3);
}

int (get_all_values(uint8_t x1, uint8_t *packet)){
  if (packet == NULL) return 1;
  packet[0] = x1;
  uint8_t scancode1, scancode2;
  if (util_sys_inb(KBD_OUT_BUF, &scancode1) != 0) return 1;
  if (util_sys_inb(KBD_OUT_BUF, &scancode2) != 0) return 1;
  packet[1] = scancode1;
  packet[2] = scancode2;

  printf("Byte 1:%d\nByte 2:%d\nByte 3:%d\n", x1, packet[1], packet[2]);
  return 0;
}

int (parse_packet)(uint8_t *packet, struct packet* pp){
  if (packet == NULL || pp == NULL) return 1;
  pp->bytes[0] =packet[0];
  pp->bytes[1] =packet[1];
  pp->bytes[2] =packet[2];
  pp->rb = packet[0] & BIT(1);
  pp->mb = packet[0] & BIT(2);
  pp->lb = packet[0] & BIT(0);
  if ((packet[0] & BIT(4))){
    printf("negative x\n");
    pp->delta_x = packet[1];
    pp->delta_x = - pp->delta_x;
  }
  else{
    pp->delta_x = packet[1];
  }

  if ((packet[0] & BIT(5))){
    printf("negative y\n");
    pp->delta_y = packet[2];
    pp->delta_y = -pp->delta_y;
  }

  else{
    pp->delta_y = packet[2];
  }

  pp->x_ov = packet[0] & BIT(6);

  pp->y_ov = packet[0] & BIT(7);

  return 0;
}


int (verify_obf)(uint8_t status_reg){
  return status_reg & BIT(0);
}

int (verify_timeout)(uint8_t status_reg){
  return !(status_reg & BIT(6));
}

int (verify_parity)(uint8_t status_reg){
  return !(status_reg & BIT(7));
}

int (verify_is_mouse)(uint8_t status_reg){
    return !(status_reg & BIT(5));
}

int (configure_mouse)(uint8_t command){

  uint8_t read_conf;
  if (sys_outb(STATUS_PORT, MOUSE_CONFIGURE_BEGIN)) return 1;
  if (sys_outb(KBD_OUT_BUF, command)) return 1;
  if (util_sys_inb(KBD_OUT_BUF, &read_conf)) return 1;
  return (!(read_conf == SUCCESS_CONF));
}

int (mouse_disable_data_reporting)(){
    return configure_mouse(DEACTIVATE_DATA_REPORT);
}

