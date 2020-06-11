#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include "object.h"

class Player : public GameObject {
    std::string username;

public:
    // Constructor
    explicit Player(const std::string& username);

    // Constructor y asignacion por copia deshabilitados
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    // Mueve el personaje segun la direccion dada
    void moveTo(int direction);
};

#endif // GAME_PLAYER_H
