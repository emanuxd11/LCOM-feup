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

bool mouse_is_descending(uint8_t tolerance);

bool mouse_is_ascending(uint8_t tolerance);

void stateMachineInvertedV(uint8_t tolerance, uint8_t x_len);

void moveMouse(int *mouse_x_pos, int *mouse_y_pos);



