#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "i8042.h"

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"

extern uint8_t scancode;
extern bool isRead;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("PT-PT");

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
  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
