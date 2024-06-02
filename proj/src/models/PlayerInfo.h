#ifndef _PLAYERINFO_H_
#define _PLAYERINFO_H_

#include <stdbool.h>


typedef struct {
    bool isPetting;
} PlayerInfo;

PlayerInfo* newPlayerInfo();
void deletePlayerInfo(PlayerInfo* playerInfo);

#endif
