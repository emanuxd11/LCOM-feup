#include "controllerMouse.h"
uint8_t delta_x_sum=0,delta_y_sum=0;
bool hasLeftClick = false;
mouseState state = INIT;


bool mouse_is_descending(uint8_t tolerance){
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

bool mouse_is_ascending(uint8_t tolerance){
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




void stateMachineInvertedV(int tolerance, int x_len){
switch(state){

      case INIT:
      delta_x_sum=0;
            delta_y_sum=0;
      printf("begin state machine\n");
        if(mouse_packet.lb && !mouse_packet.rb && !mouse_packet.mb){ 
          state = DUP;
        }

        break;

      case DUP:
      printf("Mouse ascending\n");
        if(mouse_packet.rb || mouse_packet.mb){
          state = FAIL;
        }
        if(mouse_is_ascending(tolerance)){
          state = DUP;

          if(!mouse_packet.rb && !mouse_packet.mb && !mouse_packet.lb){
            state = VERTEX;
            if(delta_x_sum < x_len || delta_y_sum/delta_x_sum < 1){
              state = FAIL;
            }
            delta_x_sum=0;
            delta_y_sum=0;
          }
        }
        
        else{
          state = FAIL;
        }

        break;
      
      case VERTEX:
      printf("Mouse vertex\n");


      if(delta_x_sum > tolerance || delta_y_sum > tolerance){
              state = FAIL;
            }


        if(mouse_packet.lb){
          delta_x_sum= 0;
          delta_y_sum = 0;
          state = DDOWN;
        }
      

        break;

      case DDOWN:
      printf("Mouse descending\n");
        if(mouse_packet.rb || mouse_packet.mb){
          state =  FAIL;
        }
        if(mouse_is_descending(tolerance)){

          state = DDOWN;

          if(!mouse_packet.lb && !mouse_packet.mb && !mouse_packet.rb){
            state = END;

            if(delta_x_sum < x_len || (abs(delta_y_sum) / abs(delta_x_sum)) < 1){
              state = FAIL;
            }
          }
        }
        else{
          state = FAIL;
        }

        break;

      case FAIL:
      printf("Gesture failed\n");
      break;

      case END:
      printf("Gesture complete\n");
      break;
        
    }

    delta_x_sum += mouse_packet.delta_x;
    delta_y_sum += mouse_packet.delta_y;


}


void moveMouse(int *mouse_pos_x, int *mouse_pos_y){

  if (mouse_packet.lb){
    hasLeftClick = true;
  }

  else{
    hasLeftClick = false;
  }


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



