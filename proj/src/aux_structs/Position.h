#ifndef _POSITION_H_
#define _POSITION_H_

typedef struct {
    int x;
    int y;
} Position;

Position *newPosition(int x, int y);

#endif
