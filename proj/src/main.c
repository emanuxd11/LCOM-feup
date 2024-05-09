#include <lcom/lcf.h>
#include <lcom/timer.h>

#include "drivers/gpu.h"
#include "drivers/keyboard.h"
#include <stdbool.h>
#include <stdint.h>
#include "images/cats/cat0.xpm"
#include "viewer/gameView.h"
#include "models/Game.h"

extern uint8_t scancode;

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");
  if (lcf_start(argc, argv))
    return 1;
  lcf_cleanup();
  return 0;
}

int(proj_main_loop)() {

  Game* game = createNewGame();

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

  int ipc_status;
  int r;
  message msg;

  while (scancode != ESC_BREAK) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_timer) {
            if (drawGame(game) != 0) scancode = ESC_BREAK;
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
  if (vg_exit() != 0)
    return 1;
  
  free(game);
  return 0;
}
