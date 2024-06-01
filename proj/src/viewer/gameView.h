#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include <lcom/lcf.h>

#include <math.h>

#include "drivers/gpu.h"
#include "../models/Game.h"
#include "../models/Datetime.h"
#include "../models/Cloud.h"
#include "../models/CatInfo.h"

#define SKY_SPLIT 0.40


int drawGame(Game *game);

int drawMenu(Game *game);

int drawInstructions();

int drawButton(const char text[], int x_center, int y_center, int width, int height, uint8_t color);

// int draw_background();

int drawSky();
int drawGrass();
int drawScenery();

int drawClouds(Cloud clouds[]);
int drawCloud(Cloud *cloud);

int drawGamePlaying(Game *game);

int drawCat(Entity *entity);

int drawMouse(int x, int y);

#endif
