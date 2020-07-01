#include "weapon.h"

Weapon::Weapon(const int new_type, const int pos_x, const int pos_y,
        const int min_damage, const int max_damage, const int mana_consumption,
        const bool is_long_distance, const bool is_magic,
        const int new_price) : minDamage(min_damage), maxDamage(max_damage),
        manaConsumption(mana_consumption), isLongDistance(is_long_distance),
        isMagic(is_magic) {
    type = new_type;
    posX = pos_x;
    posY = pos_y;
    price = new_price;
    uniqueInInventory = true;
}

Weapon::~Weapon() = default;
