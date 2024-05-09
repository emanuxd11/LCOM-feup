#include <lcom/lcf.h>
#include "../models/Game.h"
#include "drivers/gpu.h"
#include "../images/cats/smiley.xpm"
#include "../images/character/front.xpm"
#include "gameView.h"

#define YELLOW 62
#define BLUE 9
#define BROWN 20


int drawGame(Game* game){
    if (game->state == MENU_STATE){
        if (drawMenu(game) != 0) return 1;
    }
    else{
        if (drawGamePlaying(game) != 0) return 1;
    }

    return 0;
}


int drawMenu(Game* game){
    // Background color of the menu (YELLOW)
    if (set_background_color(0x105, YELLOW) != 0) return 1;

    if (draw_xpm((xpm_map_t) arrow_cursor_xpm, 20, 20) != 0) return 1;

    // TODO: CHANGE THIS FROM HARD CODED TO VARIOUS IN GAME DATA STRUCTURE
    if (drawButton("hey", 512, 300, 200, 50, BLUE) != 0) return 1;

    if (drawButton("hey", 512, 400, 200, 50, BLUE) != 0) return 1;
    return 0;
}

int drawGamePlaying(Game* game){
    if (set_background_color(0x105, BROWN) != 0) return 1;

    if (draw_xpm((xpm_map_t) front, game->room->player.position.x, game->room->player.position.y) != 0) return 1;

    // TODO: Draw cats

    // TODO: Draw Human
    return 0;
}

int drawButton(const char text[], int x_center, int y_center, int width, int height, uint8_t color){
    int x_init = x_center - width / 2;

    int y_init = y_center - height / 2;

    if (draw_rectangle(0x105, x_init, y_init, width, height, color) != 0) return 1;

    return 0;
}

