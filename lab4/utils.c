#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  if (lsb == NULL) return -1;

  *lsb = val;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL) return -1;
  *msb = val >> 8;

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {

  if (value == NULL) return -1;
  
  uint32_t read_value;

  if (sys_inb(port, &read_value) != 0) return 1;

  *value = read_value;

  return 0;
}
