#include "gameView.h"

#include "../images/cats/cat0.xpm"
#include "../images/character/front.xpm"
#include "../images/scenery/cloud.xpm"
#include "../images/logo.xpm"
#include "../images/mouse.xpm"

#define YELLOW 62
#define BLUE 9
#define SKY_DAY 27
#define SKY_NIGHT 8
#define BROWN 20
#define GREEN_GRASS 2

extern int mouse_pos_x, mouse_pos_y;
extern uint16_t x_res, y_res;
extern Datetime datetime;

int drawGame(Game *game) {

  if (game->state == MENU_STATE) {
    if (drawMenu(game) != 0) return 1;
  } else {
    if (drawGamePlaying(game) != 0) return 1;
  }

  return 0;
}

int drawMenu(Game *game) {
  // Background color of the menu (YELLOW)
  if (set_background_color(0x105, YELLOW) != 0) return 1;

  if (draw_xpm((xpm_map_t) logo, 512 - 458 / 2, 100) != 0) return 1;

  // TODO: CHANGE THIS FROM HARD CODED TO VARIOUS IN GAME DATA STRUCTURE
  if (drawButton("hey", 512, 300, 200, 50, BLUE) != 0) return 1;

  if (drawButton("hey", 512, 400, 200, 50, BLUE) != 0) return 1;

  return 0;
}

int drawGamePlaying(Game *game) {
  // Background drawing
  if (drawGrass()) return 1;
  if (drawSky()) return 1;
  if (drawClouds(game->room->clouds)) return 1;

  // if (draw_background() != 0) return 1;

  // Cats drawing
  for (int i = 0; i < 10; i++) {
    if (drawCat(&game->room->cats[i]) != 0) return 1;
  }

  // Player drawing
  if (draw_xpm((xpm_map_t) front, game->room->player.position.x, game->room->player.position.y) != 0) return 1;

  if (drawMouse(mouse_pos_x, mouse_pos_y) != 0) {
    printf("Error drawing mouse");
    return 1;
  }

  // copy image to main buffer
  if (update_front_buffer() != 0) {
    return 1;
  }

  return 0;
}

int drawCat(Entity *entity) {
  // TODO switch case to get cat type
  return draw_xpm((xpm_map_t) cat0, entity->position.x, entity->position.y) != 0;
}

int drawClouds(Cloud clouds[]) {
  for (int i = 0; i < CLOUD_QNT; i++) {
    drawCloud(&clouds[i]);
  }

  return 0;
}

int drawCloud(Cloud *cloud) {
  draw_xpm((xpm_map_t) cloud0, cloud->x, cloud->y);
  if (cloud->x + cloud_width > x_res) {
    draw_xpm((xpm_map_t) cloud0, cloud->x - x_res, cloud->y);
  }
  if (cloud->x > x_res) {
    cloud->x = 0;
  }
  cloud->x += cloud->velocity/5;

  return 0;
}

int drawGrass() {
  if (draw_rectangle(0x105, 0, y_res * SKY_SPLIT, x_res, y_res * (1 - SKY_SPLIT), GREEN_GRASS) != 0) {
    return 1;
  }

  return 0;
}

int drawSky() {
  uint16_t sky_color;

  if (datetime.hours >= 21 && datetime.hours < 7) {
    sky_color = SKY_NIGHT;
  } else {
    sky_color = SKY_DAY;
  }

  if (draw_rectangle(0x105, 0, 0, x_res, y_res * SKY_SPLIT, sky_color) != 0) {
    return 1;
  }

  return 0;
}

int drawButton(const char text[], int x_center, int y_center, int width, int height, uint8_t color) {
  int x_init = x_center - width / 2;
  int y_init = y_center - height / 2;

  if (draw_rectangle(0x105, x_init, y_init, width, height, color) != 0) {
    return 1;
  }

  return 0;
}

int drawMouse(int x, int y) {
  return draw_xpm((xpm_map_t) mouse, x, y);
}
