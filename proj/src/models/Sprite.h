#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../font/characters.xpm"

#include "../images/menu/instructions.xpm"
#include "../images/menu/logo.xpm"
#include "../images/menu/play_game.xpm"
#include "../images/menu/quit.xpm"

#include "../images/cats/cat0.xpm"
#include "../images/cats/cat1.xpm"
#include "../images/cats/cat2.xpm"
#include "../images/cats/cat3.xpm"
#include "../images/cats/cat4.xpm"

#include "../images/character/back.xpm"
#include "../images/character/front.xpm"
#include "../images/character/left.xpm"
#include "../images/character/right.xpm"

#include "../images/mouse/mouse.xpm"

#include "../images/scenery/cloud.xpm"

#include "../images/state_machines/state_machine0.xpm"
#include "../images/state_machines/state_machine1.xpm"
#include "../images/state_machines/state_machine2.xpm"
#include "../images/state_machines/state_machine3.xpm"
#include "../images/state_machines/state_machine4.xpm"


typedef struct {
  int width;
  int height;
  uint8_t *sprite;
} Sprite;


Sprite characters[CHAR_COUNT];

Sprite mc_back;
Sprite mc_front;
Sprite mc_left;
Sprite mc_right;

Sprite menu_instructions;
Sprite menu_logo;
Sprite menu_play_game;
Sprite menu_quit;

Sprite cat0_sprite;
Sprite cat1_sprite;
Sprite cat2_sprite;
Sprite cat3_sprite;
Sprite cat4_sprite;

Sprite mouse_sprite;

Sprite cloud_sprite;

Sprite state_machine0_sprite;
Sprite state_machine1_sprite;
Sprite state_machine2_sprite;
Sprite state_machine3_sprite;
Sprite state_machine4_sprite;


Sprite load_generic_sprite(xpm_map_t xpm_map);

int load_char_sprites();

int load_menu_sprites();

int load_state_machine_sprites();

int load_cloud_sprites();

int load_cat_sprites();

int load_mouse_sprites();

int load_main_character_sprites();

int load_all_sprites();

#endif
