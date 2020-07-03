#include "weapon.h"

Weapon::Weapon(const int new_type, const int pos_x, const int pos_y,
        const int min_damage, const int max_damage, const int mana_consumption,
        const int range, const int move_velocity, const bool is_magic,
        const int new_price) : minDamage(min_damage), maxDamage(max_damage),
        manaConsumption(mana_consumption), range(range),
        moveVelocity(move_velocity), isMagic(is_magic) {
    type = new_type;
    posX = pos_x;
    posY = pos_y;
    price = new_price;
    uniqueInInventory = true;
}

Weapon::~Weapon() = default;

const bool Weapon::isLongDistance() {
    return range > 1;
}