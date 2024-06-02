#ifndef _CATINFO_H_
#define _CATINFO_H_

#include <stdbool.h>
#include <lcom/lcf.h>


enum CatColor {
    ORANGE_CAT,
    WHITE_CAT,
    BLACK_CAT,
    GRAY_CAT,
    BROWN_CAT
};

typedef struct {
    enum CatColor color;
    bool isPet;
    uint8_t petCooldown;
    uint16_t moveCountdown;
    bool isIdle;
    bool isSelected;
} CatInfo;

CatInfo* newCatInfo(); //returns new CatInfo with random color
void deleteCatInfo(CatInfo* catInfo);

#endif
