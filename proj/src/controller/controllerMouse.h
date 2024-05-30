#include <stdlib.h>
#include <stdbool.h>
#include <lcom/lcf.h> //have to include this so struct packet is known



extern struct packet mouse_packet;
extern uint8_t tolerance;
typedef enum {
  INIT,
  DUP,
  DDOWN,
  VERTEX,
  FAIL,
  END
} mouseState;




bool leftButtonPressed();

bool rightButtonPressed();

bool mouse_is_descending(int16_t tolerance);

bool mouse_is_ascending(uint8_t tolerance);

void stateMachineInvertedV(int tolerance, int x_len);

void stateMachineV(int tolerance, int x_len);

void moveMouse(int *mouse_x_pos, int *mouse_y_pos);



