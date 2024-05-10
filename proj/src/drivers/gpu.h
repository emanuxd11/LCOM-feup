#define INTNO 0x10


int (vg_enter)(uint16_t mode);

int (create_vram_buffer)(uint16_t mode);

int (draw_pixel)(uint16_t mode, uint16_t x, uint16_t y, uint32_t color);

int (draw_line)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint32_t color);

int (draw_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t color);

int (draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

int (set_background_color)(uint16_t mode, uint32_t color);

