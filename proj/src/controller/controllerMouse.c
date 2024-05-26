#include "controllerMouse.h"
uint8_t delta_x_sum=0,delta_y_sum=0;
mouseState state = INIT;


bool mouseDescending(uint8_t tolerance){
  if(mouse_packet.delta_x <= 0 && mouse_packet.delta_y <= 0){
    return true;
  }

  if(mouse_packet.delta_x <= 0 && mouse_packet.delta_y > 0 && abs(mouse_packet.delta_y)  <= tolerance){
    return true;
  }

  if(mouse_packet.delta_y <= 0 && mouse_packet.delta_x > 0 && abs(mouse_packet.delta_x) <= tolerance){
    return true;
  }

  if(mouse_packet.delta_x > 0 && abs(mouse_packet.delta_x) <= tolerance && mouse_packet.delta_y > 0 && abs(mouse_packet.delta_y) <= tolerance){
    return true;
  }

  else{
    return false;
  }
}

bool mouseAscending(uint8_t tolerance){
  if(mouse_packet.delta_x >= 0 && mouse_packet.delta_y >= 0){
    return true;
  }

  if(mouse_packet.delta_x >= 0 && mouse_packet.delta_y < 0 && mouse_packet.delta_y <= tolerance){
    return true;
  }

  if(mouse_packet.delta_y >= 0 && mouse_packet.delta_x < 0 && mouse_packet.delta_x <= tolerance){
    return true;
  }

  if(mouse_packet.delta_x < 0 && mouse_packet.delta_x <= tolerance && mouse_packet.delta_y < 0 && mouse_packet.delta_y <= tolerance){
    return true;
  }

  else{
    return false;
  }
}




bool stateMachineV(uint8_t tolerance, uint8_t x_len){
    switch(state){

      case INIT:
      printf("Beggining state machine\n");
          state = DUP;

          break;

      case DUP:
      printf("Mouse is ascending\n");
        if(mouseAscending(tolerance)){
          state = DUP;

          if(delta_x_sum > x_len || abs(delta_y_sum)/abs(delta_x_sum) > 1){
                if(mouseAscending(tolerance)){
                  state = DUP;
                }

                else{
                  state = VERTEX;
                }
            }

        }
        
        else{
          state = INIT;
        }

        break;
      
      case VERTEX:
      printf("vertex\n");

        delta_x_sum= 0;
        delta_y_sum = 0;
      

        if(abs(mouse_packet.delta_x) > tolerance || abs(mouse_packet.delta_y) > tolerance){
          state = INIT;
        }
      
        state = DDOWN;

        break;

      case DDOWN:
          printf("Mouse is desdc\n");

        if(mouseDescending(tolerance)){

          state = DDOWN;



            if(delta_x_sum > x_len || (abs(delta_y_sum) / abs(delta_x_sum)) > 1){
                if(mouseDescending(tolerance)){
                  state = DDOWN;
                }

                else{
                  state = END;
                }
              
            }
          
        }
        else{
          state = INIT;
        }

        break;

      case END:
        return true;
        
        
    }

    delta_x_sum += mouse_packet.delta_x;
    delta_y_sum += mouse_packet.delta_y;

    return false;

}


void moveMouse(int *mouse_pos_x, int *mouse_pos_y){
  *mouse_pos_x+=mouse_packet.delta_x;
  *mouse_pos_y-=mouse_packet.delta_y;

  if(*mouse_pos_x<0){
    *mouse_pos_x=0;
  }
  if(*mouse_pos_x>1024){
    *mouse_pos_x=1024;
  }
  if(*mouse_pos_y<0){
    *mouse_pos_y=0;
  }
  if(*mouse_pos_y>768){
    *mouse_pos_y=768;
  }

}



