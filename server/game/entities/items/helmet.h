#ifndef HELMET_H
#define HELMET_H

#include "item.h"

class Helmet : public Item {
    int minDefense, maxDefense;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Helmet(const int new_type, position_t new_pos,
            const int min_defense, const int max_defense, const bool is_magic,
            const int new_price);

    // Constructor y asignacion por copia deshabilitados
    Helmet(const Helmet& other) = delete;
    Helmet& operator=(const Helmet& other) = delete;

    // Destructor
    ~Helmet();
};

#endif // HELMET_H
