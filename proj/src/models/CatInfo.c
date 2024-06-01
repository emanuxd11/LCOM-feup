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
        color = ORANGE_CAT;
        break;

    case 1:
        color = WHITE_CAT;
        break;

    case 2:
        color = BLACK_CAT;
        break;

    case 3:
        color = GRAY_CAT;
        break;

    case 4:
        color = BROWN_CAT;

    default:
        color = ORANGE_CAT;
        break;
    }
    catInfo->color = color;

    return catInfo;
}

void deleteCatInfo(CatInfo* catInfo) {
    free(catInfo);
}
