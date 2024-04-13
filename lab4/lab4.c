// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "mouse.h"

extern uint8_t scancode;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    /* To be completed */
    uint8_t irq_set;

    int ipc_status;
    int r;
    message msg;

    if (mouse_subscribe_int(&irq_set) != 0) return 1;
    if (mouse_enable_data_reporting() != 0) return 1;

      while(cnt > 0){

      if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) { 
          printf("Didn't received anything :(\n");
          continue;
      }
      if (is_ipc_notify(ipc_status)){
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:		
                  if (msg.m_notify.interrupts & irq_set) { 
                    mouse_ih();
                    uint8_t x1 = scancode;
                    mouse_ih();
                    uint8_t x2 = scancode;
                    mouse_ih();
                    uint8_t x3 = scancode;
                    
                    printf("A byte was received %d, %d, %d\n", x1, x2, x3);
                    //kbd_print_scancode(is_make(scancode), scan_n_bytes(scancode), &scancode);
                    cnt--;
                  }
                  break;
              default:
                  break;	
          }
      }
    }


    if (mouse_disable_data_reporting() != 0) return 1;
    if (mouse_unsubscribe_int() != 0) return 1;
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

/*
int (mouse_test_gesture)() {
    //  To be completed 
    printf("%s: under construction\n", __func__);
    return 1;
}
*/

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
