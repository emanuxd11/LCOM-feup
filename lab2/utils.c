#include <lcom/lcf.h>

#include <stdint.h>

// get least significant byte in 16 bit val
int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if (lsb == NULL) {
    return 1;
  }
  
  *lsb = 0xFF & val;  

  return 0;
}

// get most significant byte in 16 bit val
int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL) {
    return 1;
  }

  *msb = 0xFF & (val >> 8); // by right shifting by 8 bits we're essentially making it so that it's the same as in get_LSB
  // AND with 0xFF you get the least significant, so because the most significant is now in the least significant's position, that's what we get

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t val_32;
  val_32 = 0xFF & *value;
  int ret = sys_inb(port, &val_32); // sys_inb lida com valores de 32 bits
  *value = 0xFF & val_32; // pegar nos 8 primeiros bits do valor lido para retornar na mesma variável de apenas 8 bits
  return ret;
}
