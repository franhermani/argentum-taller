#include "potion.h"

Potion::Potion(const int new_type, position_t new_pos,
        const int life_points, const int mana_points, const bool is_magic,
        const int new_price) : lifePoints(life_points),
        manaPoints(mana_points) {
    type = new_type;
    pos = new_pos;
    price = new_price;
    uniqueInInventory = false;
    isMagic = is_magic;
}

Potion::~Potion() = default;
