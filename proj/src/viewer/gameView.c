#include <lcom/lcf.h>
#include "../models/Game.h"
#include "drivers/gpu.h"


int drawGame(Game* game){
    if (game->state == MENU_STATE){
        if (set_background_color(0x105, 62) != 0) return 1;
    }
    else{
        if (set_background_color(0x105, 63) != 0) return 1;
    }

    return 0;
}
