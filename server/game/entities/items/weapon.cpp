#include "weapon.h"

Weapon::Weapon(const int weapon_type, const int attack_type,
        const int attack_sound, position_t new_pos, const int min_damage,
        const int max_damage, const int mana_consumption, const int range,
        const int move_velocity, const bool is_magic,
        const bool is_life_restorer, const int new_price) :
attackType(attack_type),
attackSound(attack_sound),
minDamage(min_damage),
maxDamage(max_damage),
manaConsumption(mana_consumption),
range(range),
moveVelocity(move_velocity),
isLifeRestorer(is_life_restorer) {
    type = weapon_type;
    pos = new_pos;
    price = new_price;
    uniqueInInventory = true;
    isMagic = is_magic;
}

Weapon::~Weapon() = default;
