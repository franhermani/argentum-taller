#include "weapon.h"

Weapon::Weapon(const int type, const int min_damage, const int max_damage,
        const int mana_consumption, const bool is_long_distance,
        const bool is_magic) : type(type), minDamage(min_damage),
        maxDamage(max_damage), manaConsumption(mana_consumption),
        isLongDistance(is_long_distance), isMagic(is_magic) {}

Weapon::~Weapon() = default;
