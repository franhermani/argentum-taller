#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item {
    int attackType;
    int minDamage, maxDamage;
    int manaConsumption;
    int range;
    int moveVelocity;
    bool isMagic, isLifeRestorer;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Weapon(const int weapon_type, const int attack_type, position_t new_pos,
            const int min_damage, const int max_damage,
            const int mana_consumption, const int range,
            const int move_velocity, const bool is_magic,
            const bool is_life_restorer, const int new_price);

    // Constructor y asignacion por copia deshabilitados
    Weapon(const Weapon& other) = delete;
    Weapon& operator=(const Weapon& other) = delete;

    // Destructor
    ~Weapon();
};

#endif // WEAPON_H
