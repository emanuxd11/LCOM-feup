#ifndef _CATINFO_H_
#define _CATINFO_H_

#include <stdbool.h>


enum CatColor {
    ORANGE,
    WHITE,
    BLACK,
    GRAY,
    BROWN
};

typedef struct {
    enum CatColor color;
    bool isPet;
    bool isAngry;
} CatInfo;

CatInfo* newCatInfo(); //returns new CatInfo with random color
void deleteCatInfo(CatInfo* catInfo);

#endif
