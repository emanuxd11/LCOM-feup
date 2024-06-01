#ifndef _POSITION_H_
#define _POSITION_H_

typedef struct {
    double x;
    double y;
} Position;


Position *newPosition(int x, int y);
void deletePosition(Position* position);

#endif
