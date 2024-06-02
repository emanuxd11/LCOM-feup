#include <lcom/lcf.h>

#include "Sprite.h"


Sprite characters[CHAR_COUNT];

int load_char_sprites() {
  for (int i = 0; i < character_count; i++) {
    xpm_image_t img; 
    uint8_t *sprite = xpm_load(xpm_map_characters[i], XPM_INDEXED, &img);
    if (sprite == NULL) {
      printf("load_chars(): error loading character xpms\n");
      return 1;
    }

    characters[i].width = img.width;
    characters[i].height = img.height;
    characters[i].sprite = sprite;
  }

  return 0;
}
