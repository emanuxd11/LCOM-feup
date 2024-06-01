#ifndef _GPU_H_
#define _GPU_H_

#define INTNO 0x10

#include <string.h>

#include "../font/characters.xpm"


int (enter_video_mode)(uint16_t mode);

int (exit_video_mode)();

int (create_vram_buffer)(uint16_t mode);

int (draw_pixel)(uint16_t mode, uint16_t x, uint16_t y, uint32_t color);

int (draw_line)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint32_t color);

int (draw_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t color);

int (draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

int (draw_xpm_single_color)(xpm_map_t xpm, uint16_t x, uint16_t y, uint32_t color);

int (get_char_xpm_idx)(char ch);

int (draw_text)(const char *text, uint16_t x, uint16_t y, uint32_t color);

int (set_background_color)(uint16_t mode, uint32_t color);

int (update_front_buffer)();

#endif
