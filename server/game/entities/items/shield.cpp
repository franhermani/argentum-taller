#include "shield.h"

Shield::Shield(const int new_type, position_t new_pos,
        const int min_defense, const int max_defense, const int new_price) :
        minDefense(min_defense), maxDefense(max_defense) {
    type = new_type;
    pos = new_pos;
    price = new_price;
    uniqueInInventory = true;
}

Shield::~Shield() = default;
