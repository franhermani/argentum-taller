#ifndef SHIELD_H
#define SHIELD_H

#include "item.h"

class Shield : public Item {
    int minDefense, maxDefense;
    int price;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Shield(const int new_type, const int pos_x, const int pos_y,
            const int min_defense, const int max_defense,
            const int new_price);

    // Constructor y asignacion por copia deshabilitados
    Shield(const Shield& other) = delete;
    Shield& operator=(const Shield& other) = delete;

    // Destructor
    ~Shield();
};

#endif // SHIELD_H
