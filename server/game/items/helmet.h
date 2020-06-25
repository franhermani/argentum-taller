#ifndef HELMET_H
#define HELMET_H

#include "item.h"

class Helmet : public Item {
    int minDefense, maxDefense;
    bool isMagic;

    friend class Player;
    friend class Equations;
    friend class ServerProtocol;

public:
    // Constructor
    Helmet(const int new_type, const int pos_x, const int pos_y,
            const int min_defense, const int max_defense, bool is_magic);

    // Constructor y asignacion por copia deshabilitados
    Helmet(const Helmet& other) = delete;
    Helmet& operator=(const Helmet& other) = delete;

    // Destructor
    ~Helmet();
};

#endif // HELMET_H
