#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item {
    int minDamage, maxDamage;
    int manaConsumption;
    int range;
    int moveVelocity;
    bool isMagic;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Weapon(const int new_type, const int pos_x, const int pos_y,
            const int min_damage, const int max_damage,
            const int mana_consumption, const int range,
            const int move_velocity, const bool is_magic,
            const int new_price);

    // Constructor y asignacion por copia deshabilitados
    Weapon(const Weapon& other) = delete;
    Weapon& operator=(const Weapon& other) = delete;

    // Destructor
    ~Weapon();

    // Devuelve true si el arma es de larga distancia (range > 1)
    // False en caso contrario
    const bool isLongDistance();
};

#endif // WEAPON_H
