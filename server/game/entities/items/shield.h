#ifndef SHIELD_H
#define SHIELD_H

#include "item.h"

class Shield : public Item {
    int minDefense, maxDefense;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Shield(const int new_type, position_t new_pos,
            const int min_defense, const int max_defense,
            const bool is_magic, const int new_price);

    // Constructor y asignacion por copia deshabilitados
    Shield(const Shield& other) = delete;
    Shield& operator=(const Shield& other) = delete;

    // Destructor
    ~Shield();
};

#endif // SHIELD_H
