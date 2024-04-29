#include <lcom/lcf.h>
#include <lcom/timer.h>

#include "drivers/gpu.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include <stdbool.h>
#include <stdint.h>

extern uint8_t scancode;
int byte_order=0;
extern bool finished;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)() {

<<<<<<< HEAD

int (proj_main_loop)(){

  if (timer_set_frequency(0, 60) != 0) return 1;
  uint8_t irq_set_timer, irq_set_keyboard, irq_set_mouse;
  
  if (timer_subscribe_int(&irq_set_timer) != 0) return 1;
  if (kbd_subscribe_int(&irq_set_keyboard) != 0) return 1;
  if(mouse_subscribe_int(&irq_set_mouse) != 0) return 1;
  if (vg_enter(0x105) != 0) return 1;
=======
  if (timer_set_frequency(0, 60) != 0)
    return 1;
  uint8_t irq_set_timer;
  uint8_t irq_set_keyboard;

  if (timer_subscribe_int(&irq_set_timer) != 0)
    return 1;
  if (kbd_subscribe_int(&irq_set_keyboard) != 0)
    return 1;
  if (vg_enter(0x105) != 0)
    return 1;

  if (create_vram_buffer(0x105) != 0) return 1;

  if (draw_rectangle(0x105, 100, 100, 100, 100, 0x20) != 0) return 1;
>>>>>>> a844e7454084ed87479b186390dd6ff38f62850d

  int ipc_status;
  int r;
  int count = 0;
  int oscillations = 0;
  message msg;

  while (scancode != ESC_BREAK) {

      if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          continue;
      }
      if (is_ipc_notify(ipc_status)) { 
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:		
                  if (msg.m_notify.interrupts & irq_set_timer) {
                      oscillations++;
                      if (oscillations == 60) {
                        timer_print_elapsed_time();
                        oscillations = 0;
                        count++;  
                      }
                  }

                  if (msg.m_notify.interrupts & irq_set_keyboard){
                    kbc_ih();
                  }

                  if(msg.m_notify.interrupts & irq_set_mouse){
                    mouse_ih();

                    if(finished){
                      count++;
                      byte_order = 0;
                      finished = false;
                      mouse_print_packet(&mouse_packet);
                    }

                  }

                  break;
              default:
                  break;
          }

          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();
          }

          break;
        default:
          break;
      }
    }
    else {
    }
  }
    
  printf("Hello, World!\n");
  if (timer_unsubscribe_int() != 0)
    return 1;
  if (kbd_unsubscribe_int() != 0)
    return 1;
  if(mouse_unsubscribe_int() != 0)
    return 1;
  if(kbc_restore_mouse() != 0)
    return 1;
  if (vg_exit() != 0)
    return 1;
  return 0;
}
