#ifndef POTION_H
#define POTION_H

#include "item.h"

class Potion : public Item {
    int lifePoints, manaPoints;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Potion(const int new_type, position_t new_pos,
            const int life_points, const int mana_points,
            const int new_price);

    // Constructor y asignacion por copia deshabilitados
    Potion(const Potion& other) = delete;
    Potion& operator=(const Potion& other) = delete;

    // Destructor
    ~Potion();
};

#endif // POTION_H
