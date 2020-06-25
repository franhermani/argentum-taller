#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"

class Armor : public Item {
    int minDefense, maxDefense;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Armor(const int new_type, const int pos_x, const int pos_y,
            const int min_defense, const int max_defense);

    // Constructor y asignacion por copia deshabilitados
    Armor(const Armor& other) = delete;
    Armor& operator=(const Armor& other) = delete;

    // Destructor
    ~Armor();
};

#endif // ARMOR_H
