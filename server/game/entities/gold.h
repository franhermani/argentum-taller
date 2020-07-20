#ifndef GOLD_H
#define GOLD_H

#include "../../../common/utilities/position.hpp"

class Gold {
    int quantity;
    position_t pos;

    friend class World;
    friend class Player;
    friend class ServerProtocol;

public:
    // Constructor
    Gold(const int quantity, position_t new_pos);

    // Constructor y asignacion por copia deshabilitados
    Gold(const Gold& other) = delete;
    Gold& operator=(const Gold& other) = delete;
};

#endif // GOLD_H
