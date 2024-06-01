#include "controllerMouse.h"
int delta_x_sum=0,delta_y_sum=0;
bool hasLeftClick = false;
mouseState state = INIT;


bool mouse_is_descending(int16_t tolerance){
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


      if(mouse_packet.lb && !mouse_packet.rb && !mouse_packet.mb){ 
        state = DUP;
      }

      break;

      case DUP:
        if(mouse_packet.rb || mouse_packet.mb){
          state = FAIL;
        }
        if(mouse_is_ascending(tolerance)){
          state = DUP;

          if(!mouse_packet.rb && !mouse_packet.mb && !mouse_packet.lb){
            state = VERTEX;
            if(delta_x_sum < x_len || (float) abs(delta_y_sum)/(float) abs(delta_x_sum) < 0.5 || delta_y_sum< 0){
              if( delta_x_sum==0 && delta_y_sum==0){ //when cats are clicked, avoid failing
                state = INIT;
               }

              else{
              state = FAIL;
              }
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
      break;

      case END:
      break;

      default:break;
        
    }

    delta_x_sum += mouse_packet.delta_x;
    delta_y_sum += mouse_packet.delta_y;


}


void stateMachineV(int tolerance, int x_len){
  switch(state){
      case INIT:
        delta_x_sum=0;
        delta_y_sum=0;


        if(mouse_packet.lb && !mouse_packet.rb && !mouse_packet.mb){ 
          state = DDOWN;
        }

        break;

      case DDOWN:
        if(mouse_packet.rb || mouse_packet.mb){
          state = FAIL;
        }

        if(mouse_is_descending(tolerance)){
          state = DDOWN;

          if(!mouse_packet.rb && !mouse_packet.mb && !mouse_packet.lb){
            
            state = VERTEX;
            if(delta_x_sum < x_len || (float) abs(delta_y_sum)/(float) abs(delta_x_sum) < 0.5 || delta_y_sum> 0){
              
              if( delta_x_sum==0 && delta_y_sum==0){ //when cats are clicked, avoid failing
                state = INIT;
               }

              else{
              state = FAIL;
              }
            }
            delta_x_sum=0;
            delta_y_sum=0;
          }
        }

        else{

          state = FAIL;
        }

        break;

      case DUP:

        if(mouse_packet.rb || mouse_packet.mb){
          state = FAIL;
        }
        if(mouse_is_ascending(tolerance)){
          state = DUP;

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
      
      case VERTEX:


        if(delta_x_sum > tolerance || delta_y_sum > tolerance){
          state = FAIL;
        }


        if(mouse_packet.lb){
          delta_x_sum= 0;
          delta_y_sum = 0;
          state = DUP;
        }
      

        break;

      

      case FAIL:
      break;

      case END:
      break;

      default:break;

        
    }

    delta_x_sum += mouse_packet.delta_x;
    delta_y_sum += mouse_packet.delta_y;


}


void stateMachineVLine(int tolerance, int y_len){
  switch(state){
    case INIT:

        delta_x_sum=0;
        delta_y_sum=0;

        if(mouse_packet.lb && !mouse_packet.rb && !mouse_packet.mb){ 
          state = DUP;
        }

    break;

    case DUP:

      if(mouse_packet.rb || mouse_packet.mb){
        state = FAIL;
      }

      if(mouse_is_ascending(tolerance)){
        state = DUP;

        if(!mouse_packet.lb && !mouse_packet.mb && !mouse_packet.rb){
          state = END;

          if(abs(delta_y_sum) < y_len || ((float) abs(delta_x_sum)/(float) abs(delta_y_sum) >= 0.1) ){
            
            state = FAIL;
          }
        }

      }

      else{
        state = FAIL;
      }

    break;

    case FAIL:
    break;

    case END:
    break;

    default:
    break;

  }

  delta_x_sum += mouse_packet.delta_x;
  delta_y_sum += mouse_packet.delta_y;

}

void stateMachineHLine (int tolerance, int x_len){
  switch(state){
    case INIT:

        delta_x_sum=0;
        delta_y_sum=0;

        if(mouse_packet.lb && !mouse_packet.rb && !mouse_packet.mb){ 
          state = DSIDE;
        }

    break;

    case DSIDE:

      if(mouse_packet.rb || mouse_packet.mb){
        state = FAIL;
      }

      if(mouse_is_ascending(tolerance) || mouse_is_descending(tolerance)){
        state = DSIDE;

        if(!mouse_packet.lb && !mouse_packet.mb && !mouse_packet.rb){
          state = END;

          if(abs(delta_x_sum) < x_len || ((float) abs(delta_y_sum)/(float) abs(delta_x_sum) >= 0.1 )){
            state = INIT;
          }
        }

      }

      else{
        state = INIT;
      }

    break;

    case FAIL:
      state = FAIL;
    break;

    case END:
    break;

    default:
    break;

  }

  delta_x_sum += mouse_packet.delta_x;
  delta_y_sum += mouse_packet.delta_y;

}

void stateMachineDLine(int tolerance, int y_len){
  switch(state){
    case INIT:

        delta_x_sum=0;
        delta_y_sum=0;

        if(mouse_packet.lb && !mouse_packet.rb && !mouse_packet.mb){ 
          state = DUP;
        }

    break;

    case DUP:

      if(mouse_packet.rb || mouse_packet.mb){
        state = FAIL;
      }

      if(mouse_is_ascending(tolerance)){
        state = DUP;

        if(!mouse_packet.lb && !mouse_packet.mb && !mouse_packet.rb){
          state = END;

          if(abs(delta_y_sum) < y_len || (float) abs(delta_x_sum)/(float) abs(delta_y_sum) <= 0.8 || (float) abs(delta_x_sum)/(float) abs(delta_y_sum) >= 1.5 ) {
            
            state = FAIL;
          }
        }

      }

      else{
        state = FAIL;
      }

    break;

    case FAIL:

    break;

    case END:

    break;

    default:
    
    break;

  }

  delta_x_sum += mouse_packet.delta_x;
  delta_y_sum += mouse_packet.delta_y;

}





void moveMouse(int *mouse_pos_x, int *mouse_pos_y){

  if(mouse_packet.x_ov || mouse_packet.y_ov){
    printf("x:%d\ny:%d\n",mouse_packet.delta_x,mouse_packet.delta_y);
    printf("a\n");
    return;
  }


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



