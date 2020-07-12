#ifndef GOLD_H
#define GOLD_H

#include "../../../common/defines/position.h"

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

    // Actualiza la posicion (posX, posY) del oro
    void updatePosition(position_t new_pos);
};

#endif // GOLD_H
