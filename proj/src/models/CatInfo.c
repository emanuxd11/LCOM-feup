#include "CatInfo.h"
#include "../utils/utils.h"
#include <stdlib.h>

CatInfo* newCatInfo() {
    CatInfo* catInfo = (CatInfo*) malloc(sizeof(CatInfo));

    catInfo->isPet = false;
    catInfo->petCooldown = 0;
    catInfo->moveCountdown = 0;
    catInfo->isIdle = true;

    enum CatColor color;

    switch (randomNumer(0, 4))
    {
    case 0:
        color = ORANGE;
        break;

    case 1:
        color = WHITE;
        break;

    case 2:
        color = BLACK;
        break;

    case 3:
        color = GRAY;
        break;

    case 4:
        color = BROWN;

    default:
        color = ORANGE;
        break;
    }
    catInfo->color = color;

    return catInfo;
}

void deleteCatInfo(CatInfo* catInfo) {
    free(catInfo);
}
