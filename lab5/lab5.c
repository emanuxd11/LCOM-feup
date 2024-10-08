// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "gpu.h"
#include "keyboard.h"

extern uint8_t scancode;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if (vg_enter(mode) != 0) return 1;

  sleep(delay);

  if(vg_exit() != 0) return 1;

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  if (create_vram_buffer(mode) != 0) return 1;

  if (vg_enter(mode) != 0) return 1;

  if (draw_rectangle(mode, x, y, width, height, color) != 0){
    printf("Error drawing a rectangle\n");
    if(vg_exit() != 0) return 1;
     return 1;
  }

  uint8_t irq_set;
  int ipc_status;
  int r;
  message msg;
  uint32_t cnt = 0;

  if(kbd_subscribe_int(&irq_set)) return -1;


    while(scancode != ESC_BREAK){

      if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) { 
          printf("Didn't received anything :(\n");
          continue;
      }
      if (is_ipc_notify(ipc_status)){
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:		
                  if (msg.m_notify.interrupts & irq_set) { 
                    kbc_ih();
                    kbd_print_scancode(is_make(scancode), scan_n_bytes(scancode), &scancode);
                    cnt++;
                  }
                  break;
              default:
                  break;	
          }

          if (scancode == ESC_BREAK){
            break;
          }
      }
    }
  
  if (kbd_unsubscribe_int()) return -1;

  if(vg_exit() != 0) return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__,
         mode, no_rectangles, first, step);

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  if (create_vram_buffer(0x105) != 0) return 1;

  if (vg_enter(0x105) != 0) return 1;
  
  if (draw_xpm(xpm, x, y) != 0) return 1;

    uint8_t irq_set;
  int ipc_status;
  int r;
  message msg;
  uint32_t cnt = 0;

  if(kbd_subscribe_int(&irq_set)) return -1;


    while(scancode != ESC_BREAK){

      if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) { 
          printf("Didn't received anything :(\n");
          continue;
      }
      if (is_ipc_notify(ipc_status)){
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:		
                  if (msg.m_notify.interrupts & irq_set) { 
                    kbc_ih();
                    kbd_print_scancode(is_make(scancode), scan_n_bytes(scancode), &scancode);
                    cnt++;
                  }
                  break;
              default:
                  break;	
          }

          if (scancode == ESC_BREAK){
            break;
          }
      }
    }
  
  if (kbd_unsubscribe_int()) return -1;

  if(vg_exit() != 0) return 1;

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
