#ifndef SHIELD_H
#define SHIELD_H

#include "item.h"

class Shield : public Item {
    int type;
    int minDefense;
    int maxDefense;

    friend class Player;

public:
    // Constructor
    Shield(const int type,const int min_defense, const int max_defense);

    // Constructor y asignacion por copia deshabilitados
    Shield(const Shield& other) = delete;
    Shield& operator=(const Shield& other) = delete;

    // Destructor
    ~Shield();
};

#endif // SHIELD_H
