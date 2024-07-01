#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  if (lcf_start(argc, argv)) {
    return 1;
  }

  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {

  uint8_t config;
  if (timer_get_conf(timer, &config) == 1) return 1;

  timer_display_conf(timer, config, field);

  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  return timer_set_frequency(timer, freq);
}

int(timer_test_int)(uint8_t time) {

  uint8_t irq_set;
  if (timer_subscribe_int(&irq_set) != 0) {
    return 1;
  }

  // if (timer_set_frequency(0, 120) != 0) {
  //   printf("\ntimer_test_int(): error in timer_set_frequency()\n");
  //   return 1;
  // }

  int ipc_status, r, elapsed_s = 0, oscillations = 0;
  message msg;
  while (elapsed_s < time) { // a different condition may be used here
    // get a request message
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    // received notification
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set) {
            oscillations++;
            if (oscillations == 60) {
              timer_print_elapsed_time();
              oscillations = 0;
              elapsed_s++;
            }
          }
          break;
        default:
        break; // no other notifications expected: do nothing
      }
    } else { // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  if (timer_unsubscribe_int() != 0) {
    return 1;
  }

  return 0;
}
