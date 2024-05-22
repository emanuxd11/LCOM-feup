#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdbool.h>
#include <stdint.h>

#include "drivers/gpu.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/rtclock.h"

#include "models/Game.h"
#include "controller/controllerKeyboard.h"
#include "controller/controllerMouse.h"
#include "viewer/gameView.h"

#include "images/cats/cat0.xpm"


extern uint8_t scancode;
extern struct packet mouse_packet;
int byte_order_packet = 0;
extern bool finished;
int mouse_pos_x=0, mouse_pos_y=0;


int main(int argc, char *argv[]) {

  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  if (lcf_start(argc, argv)) {
    return 1;
  }

  lcf_cleanup();

  return 0;
}

int (proj_main_loop)() {

  Game *game = createNewGame();

  uint8_t irq_set_timer;
  uint8_t irq_set_keyboard;
  uint8_t irq_set_mouse;

  message msg;
  int ipc_status;
  int r;

  if (timer_set_frequency(0, 60) != 0) {
    return 1;
  }

  if (timer_subscribe_int(&irq_set_timer) != 0) {
    return 1;
  }

  if (kbd_subscribe_int(&irq_set_keyboard) != 0) {
    return 1;
  }

  if (mouse_subscribe_int(&irq_set_mouse) != 0) {
    return 1;
  }

  if(issue_cmd_to_mouse(ENABLE_DATA_REP)!=0){ //enable data report
      printf("Error enabling data report\n");
      return 1;
  }


  if (enter_video_mode(0x105) != 0) {
    return 1;
  }

  if (create_vram_buffer(0x105) != 0) {
    return 1;
  }

  while (game->state != LEAVE_STATE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          // processes the view -> for every interrupt of timer (60 Hz) draws the game
          if (msg.m_notify.interrupts & irq_set_timer) {
            if (drawGame(game) != 0) {
              game->state = LEAVE_STATE;
            }
            
          }

          // Keyboard Interrupts -> Go to the controller to check what to do with it
          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();

            if (control_game(game, scancode) != 0) {
              return 1;
            }
          }

          if (msg.m_notify.interrupts & irq_set_mouse) {

              mouse_ih();

              if(finished){
                //packet is read
                byte_order_packet = 0;
                finished = false;
              }
              
              moveMouse(&mouse_pos_x, &mouse_pos_y);

          }

          break;
        default:
          break;
      }
    }
    else { }
  }

  printf("Hello, World!\n");
  if (timer_unsubscribe_int() != 0) {
    return 1;
  }

  if (kbd_unsubscribe_int() != 0) {
    return 1;
  }

  if (mouse_unsubscribe_int() != 0) {
    return 1;
  }

  if (kbc_restore_mouse() != 0) { // disable data rep
    return 1;
  }

  if (exit_video_mode() != 0) {
    return 1;
  }

  free(game);

  return 0;
}
