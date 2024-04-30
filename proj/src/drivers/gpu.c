#include <stdint.h>
#include <stdio.h>
#include <lcom/lcf.h>
#include "gpu.h"

static char *video_ram;

vbe_mode_info_t modeInfo;


int (vg_enter)(uint16_t mode) {
  reg86_t r86;
   
  /* Specify the appropriate register values */
  
  memset(&r86, 0, sizeof(r86));	/* zero the structure */

  r86.intno = INTNO; /* BIOS video services */
  r86.ah = 0x4F;    /* Set Video Mode function */
  r86.al = 0x02;    /* 80x25 text mode */
  r86.bx = mode | BIT(14);
  
  /* Make the BIOS call */

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }
  return 0;
}


int (create_vram_buffer)(uint16_t mode){

    if (vbe_get_mode_info(mode, &modeInfo) != 0) return 1;

    uint8_t n_bits_per_pixel = modeInfo.BitsPerPixel;
    uint8_t n_bytes_per_pixel;

    if (n_bits_per_pixel == 15) n_bytes_per_pixel = 2;
    else n_bytes_per_pixel = n_bits_per_pixel / 8;

    uint32_t buffer_size = n_bytes_per_pixel * modeInfo.XResolution * modeInfo.YResolution;

    struct minix_mem_range buffer;

    buffer.mr_base = modeInfo.PhysBasePtr;

    buffer.mr_limit = modeInfo.PhysBasePtr + buffer_size;

    if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &buffer) != 0) return 1;

    video_ram = vm_map_phys(SELF, (void*) buffer.mr_base, buffer_size);

    if (video_ram == NULL) return 1;

    return 0;
}

int (draw_pixel)(uint16_t mode, uint16_t x, uint16_t y, uint32_t color){

    if (x < 0 || y < 0 || x > modeInfo.XResolution || y > modeInfo.YResolution) return 0;
    uint8_t n_bytes_per_pixel = 0;

    if (modeInfo.BitsPerPixel == 15) n_bytes_per_pixel = 2;
    else n_bytes_per_pixel = modeInfo.BitsPerPixel / 8;

    uint32_t buffer_index = (y * modeInfo.XResolution + x) * n_bytes_per_pixel;

    if (memcpy(&video_ram[buffer_index], &color, n_bytes_per_pixel) == NULL) return 1;


    return 0;
}

int (draw_line)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint32_t color){
    for (int i = 0; i < width; i++){
        if (draw_pixel(mode, x + i, y, color) != 0) return 1;
    }

    return 0;

}

int (draw_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t color){
    for (int i = 0; i < height; i++){
        if (draw_line(mode, x, y + i, width, color) != 0) return 1;
    }

    return 0;
}

int (set_background_color)(uint16_t mode, uint32_t color){
     for (int x = 0; x < modeInfo.XResolution; x++){
        for (int y = 0; y < modeInfo.YResolution; y++){
            if (draw_pixel(mode, x, y, color) != 0) return 1;
        }
     }
     return 0;
}

int (draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y){
    enum xpm_image_type type = XPM_INDEXED;
    xpm_image_t img;
    uint8_t *sprite = xpm_load(xpm, type, &img);

    for (int i = 0; i < img.height; i++){
        for (int j = 0; j < img.width; j++){
            draw_pixel(0x105, x + j, y + i, *sprite);
            sprite++;
        }
    }
    return 0;
}



