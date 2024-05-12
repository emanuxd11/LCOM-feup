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