#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "i8042.h"

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include <lcom/lab2.h>

extern uint8_t scancode;
extern bool isRead;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
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

  return (kbd_print_no_sysinb(0));
}

int(kbd_test_poll)() {
  uint8_t code = 0;
  while(code != ESC_BREAK){
    if (read_keyboard_buffer(&code) == 0){
      kbd_print_scancode(is_make(code), scan_n_bytes(code), &code);
    }
  }

  while(enable_interrupts()) continue;

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t irq_set_kbd;
  uint8_t irq_set_timer;
  int ipc_status;
  message msg;
  uint32_t cnt = 0;

  if (kbd_subscribe_int(&irq_set_kbd)) return 1;
  if (timer_subscribe_int(&irq_set_timer)) return 1;
  
  while(scancode != ESC_BREAK && (cnt / 60.0) < n){

      if ((driver_receive(ANY, &msg, &ipc_status)) != 0) { 
          continue;
      }
      if (is_ipc_notify(ipc_status)){
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:		
                  if (msg.m_notify.interrupts & irq_set_kbd) { 
                    kbc_ih();
                    kbd_print_scancode(is_make(scancode), scan_n_bytes(scancode), &scancode);
                    cnt = 0;
                    break;
                  }

                  else if (msg.m_notify.interrupts & irq_set_timer){
                    cnt++;
                    if (cnt % 60 == 0){
                      printf("%d seconds without interrupts\n", cnt / 60);
                    }
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
  

  if (kbd_unsubscribe_int()) return 1;

  if (timer_unsubscribe_int()) return 1;

  return (kbd_print_no_sysinb(0));
}

