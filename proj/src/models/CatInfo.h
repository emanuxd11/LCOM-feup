#ifndef _CATINFO_H_
#define _CATINFO_H_

#include <stdbool.h>
#include <lcom/lcf.h>


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
    uint8_t petCooldown;
} CatInfo;

CatInfo* newCatInfo(); //returns new CatInfo with random color
void deleteCatInfo(CatInfo* catInfo);

#endif
