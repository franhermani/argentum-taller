#ifndef HELMET_H
#define HELMET_H

#include "item.h"

class Helmet : public Item {
    int type;
    int minDefense;
    int maxDefense;
    bool isMagic;

    friend class Player;

public:
    // Constructor
    Helmet(const int type,const int min_defense, const int max_defense,
            bool is_magic);

    // Constructor y asignacion por copia deshabilitados
    Helmet(const Helmet& other) = delete;
    Helmet& operator=(const Helmet& other) = delete;

    // Destructor
    ~Helmet();
};

#endif // HELMET_H
