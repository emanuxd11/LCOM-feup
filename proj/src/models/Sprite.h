#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../font/characters.xpm"


typedef struct {
  int width;
  int height;
  uint8_t *sprite;
} Sprite;

Sprite characters[CHAR_COUNT];


int load_char_sprites();


#endif
