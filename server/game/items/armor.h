#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"

class Armor : public Item {
    int type;
    int minDefense;
    int maxDefense;

    friend class Player;

public:
    // Constructor
    Armor(const int type,const int min_defense, const int max_defense);

    // Constructor y asignacion por copia deshabilitados
    Armor(const Armor& other) = delete;
    Armor& operator=(const Armor& other) = delete;

    // Destructor
    ~Armor();
};

#endif // ARMOR_H
