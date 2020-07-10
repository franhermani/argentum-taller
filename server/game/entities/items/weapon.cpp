#include "weapon.h"

Weapon::Weapon(const int weapon_type, const int attack_type,
        position_t new_pos, const int min_damage,
        const int max_damage, const int mana_consumption,
        const int range, const int move_velocity, const bool is_magic,
        const bool is_life_restorer, const int new_price) :
attackType(attack_type),
minDamage(min_damage),
maxDamage(max_damage),
manaConsumption(mana_consumption),
range(range),
moveVelocity(move_velocity),
isMagic(is_magic),
isLifeRestorer(is_life_restorer) {
    type = weapon_type;
    pos = new_pos;
    price = new_price;
    uniqueInInventory = true;
}

Weapon::~Weapon() = default;
