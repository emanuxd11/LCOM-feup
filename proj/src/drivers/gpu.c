#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "gpu.h"


static char *front_buffer;
static char *back_buffer;
uint8_t bypp;
vbe_vbe_mode_info_t modeInfo;


int (vg_enter)(uint16_t mode) {
  reg86_t r86;

  memset(&r86, 0, sizeof(r86));

  r86.intno = INTNO;
  r86.ah = 0x4F;
  r86.al = 0x02;
  r86.bx = mode | BIT(14);

  if (sys_int86(&r86) != OK) {
    printf("vg_enter(): error in sys_int86()\n");
    return 1;
  }

  return 0;
}

int (create_vram_buffer)(uint16_t mode) {
  if (vbe_get_vbe_mode_info(mode, &modeInfo) != 0) {
    return 1;
  }

  uint8_t n_bits_per_pixel = modeInfo.BitsPerPixel;

  if (n_bits_per_pixel == 15) {
    bypp = 2;
  } else {
    bypp = n_bits_per_pixel / 8;
  }

  uint32_t buffer_size = bypp * modeInfo.XResolution * modeInfo.YResolution;
  struct minix_mem_range buffer;
  buffer.mr_base = modeInfo.PhysBasePtr;
  buffer.mr_limit = modeInfo.PhysBasePtr + buffer_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &buffer) != 0) {
    return 1;
  }

  front_buffer = vm_map_phys(SELF, (void *) buffer.mr_base, buffer_size);
	back_buffer = malloc(bypp * modeInfo.XResolution * modeInfo.YResolution);

  if (front_buffer == NULL) {
    return 1;
  }

  return 0;
}

int (draw_pixel)(uint16_t mode, uint16_t x, uint16_t y, uint32_t color) {
  if (x < 0 || y < 0 || x > modeInfo.XResolution || y > modeInfo.YResolution) {
    return 0;
  }

  uint8_t bypp = 0;

  if (modeInfo.BitsPerPixel == 15) {
    bypp = 2;
  } else {
    bypp = modeInfo.BitsPerPixel / 8;
  }

  uint32_t buffer_index = (y * modeInfo.XResolution + x) * bypp;

  if (memcpy(&back_buffer[buffer_index], &color, bypp) == NULL) {
		printf("draw_pixel(): error drawing pixel\n");
    return 1;
  }

  return 0;
}

int (draw_line)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint32_t color) {
  for (int i = 0; i < width; i++) {
    if (draw_pixel(mode, x + i, y, color) != 0) {
      return 1;
    }
  }

  return 0;
}

int (draw_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i < height; i++) {
    if (draw_line(mode, x, y + i, width, color) != 0) {
      return 1;
    }
  }

  return 0;
}

int (set_background_color)(uint16_t mode, uint32_t color) {
  for (int x = 0; x < modeInfo.XResolution; x++) {
    for (int y = 0; y < modeInfo.YResolution; y++) {
      if (draw_pixel(mode, x, y, color) != 0) {
        return 1;
			}
    }
  }
  return 0;
}

int (draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t *sprite = xpm_load(xpm, type, &img);

  if (sprite == NULL) {
    return 1;
  }

  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      if (*sprite == 255) {
        sprite++;
        continue;
      }

      if (draw_pixel(0x105, x + j, y + i, *sprite) != 0) {
        return 1;
      }
      sprite++;
    }
  }

  return 0;
}

int (update_front_buffer)() {
	if (!memcpy(front_buffer, back_buffer, modeInfo.XResolution * modeInfo.YResolution * bypp)) {
		printf("update_front_buffer(): error copying memory from second buffer to main buffer\n");
		return 1;
	}

	return 0;
}
