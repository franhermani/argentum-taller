#include "potion.h"

Potion::Potion(const int type, const int life_points, const int mana_points) :
        type(type), lifePoints(life_points), manaPoints(mana_points) {}

Potion::~Potion() = default;
