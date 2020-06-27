#include "potion.h"

Potion::Potion(const int new_type, const int pos_x, const int pos_y,
        const int life_points, const int mana_points, const int new_price) :
        lifePoints(life_points), manaPoints(mana_points) {
    type = new_type;
    posX = pos_x;
    posY = pos_y;
    price = new_price;
    uniqueInInventory = false;
}

Potion::~Potion() = default;
