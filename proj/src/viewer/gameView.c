#include <lcom/lcf.h>
#include "../models/Game.h"
#include "drivers/gpu.h"
#include "../images/cats/smiley.xpm"


int drawGame(Game* game){
    if (game->state == MENU_STATE){
        if (set_background_color(0x105, 61) != 0) return 1;
        if (draw_xpm((xpm_map_t) mouse_xpm, 20, 20) != 0) {
            printf("Wasn't able to draw the xpm\n");
            return 1;
        }
    }
    else{
        if (set_background_color(0x105, 63) != 0) return 1;
    }

    return 0;
}
