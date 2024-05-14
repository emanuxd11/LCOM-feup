#ifndef _CATINFO_H_
#define _CATINFO_H_

enum CatColor {
    ORANGE,
    WHITE,
    BLACK,
    GRAY,
    BROWN
};

typedef struct {
    CatColor color;
    bool isPet;
    bool isAngry;
} CatInfo;

#endif
