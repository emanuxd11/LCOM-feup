#ifndef _CONTROLLERKEYBOARD_H_
#define _CONTROLLERKEYBOARD_H_

#include "../models/Game.h"

#define TILE_UP 0x11
#define TILE_DOWN 0x1f
#define TILE_LEFT 0x1e
#define TILE_RIGHT 0x20
#define ESC_BREAK 0x81


int control_game(Game *game, uint8_t scan_code);

int control_player(Entity *entity, uint8_t scan_code);

#endif
