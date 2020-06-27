#include "helmet.h"

Helmet::Helmet(const int new_type, const int pos_x, const int pos_y,
        const int min_defense, const int max_defense, const bool is_magic,
        const int new_price) :
        minDefense(min_defense), maxDefense(max_defense), isMagic(is_magic) {
    type = new_type;
    posX = pos_x;
    posY = pos_y;
    price = new_price;
}

Helmet::~Helmet() = default;
