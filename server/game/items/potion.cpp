#include "potion.h"

Potion::Potion(const int new_type, const int pos_x, const int pos_y,
        const int life_points, const int mana_points) :
        lifePoints(life_points), manaPoints(mana_points) {
    type = new_type;
    posX = pos_x;
    posY = pos_y;
}

Potion::~Potion() = default;
