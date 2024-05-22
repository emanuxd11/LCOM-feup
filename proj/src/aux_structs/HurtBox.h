#ifndef _HURTBOX_H_
#define _HURTBOX_H_

#include <stdint.h>


typedef struct {
    uint16_t deltaX;
    uint16_t deltaY;
} HurtBox;

HurtBox *newHurtBox(uint16_t deltaX, uint16_t deltaY);

#endif
