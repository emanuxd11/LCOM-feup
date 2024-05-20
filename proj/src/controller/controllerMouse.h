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
  END
} mouseState;




bool leftButtonPressed();

bool rightButtonPressed();

bool mouseDescending(uint8_t tolerance);

bool mouseAscending(uint8_t tolerance);

bool stateMachineV(uint8_t tolerance, uint8_t x_len);



