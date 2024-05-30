#ifndef _UTILS_H_
#define _UTILS_H_

#include <lcom/lcf.h>

#include <stdint.h>


/* Some utility functions of our own */

uint8_t (bcd_to_binary)(uint8_t bcd);

int getRandomInt(int lower_bound, int upper_bound);

float getRandomFloat(float lower_bound, float upper_bound);

#endif
