#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item {
    int type;
    int minDamage;
    int maxDamage;
    int manaConsumption;
    bool isLongDistance;
    bool isMagic;

    friend class Player;
    friend class ServerProtocol;

public:
    // Constructor
    Weapon(const int type,const int min_damage, const int max_damage,
           const int mana_consumption, const bool is_long_distance,
           const bool is_magic);

    // Constructor y asignacion por copia deshabilitados
    Weapon(const Weapon& other) = delete;
    Weapon& operator=(const Weapon& other) = delete;

    // Destructor
    ~Weapon();
};

#endif // WEAPON_H
