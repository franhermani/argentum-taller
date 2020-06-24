#include "shield.h"

Shield::Shield(const int new_type, const int pos_x, const int pos_y,
        const int min_defense, const int max_defense) :
        minDefense(min_defense), maxDefense(max_defense) {
    type = new_type;
    posX = pos_x;
    posY = pos_y;
}

Shield::~Shield() = default;
