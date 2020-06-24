#ifndef POTION_H
#define POTION_H

#include "item.h"

class Potion : public Item {
    int type;
    int lifePoints;
    int manaPoints;

    friend class Player;

public:
    // Constructor
    Potion(const int type,const int life_points, const int mana_points);

    // Constructor y asignacion por copia deshabilitados
    Potion(const Potion& other) = delete;
    Potion& operator=(const Potion& other) = delete;

    // Destructor
    ~Potion();
};

#endif // POTION_H
