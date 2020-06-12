#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include "object.h"
#include "world.h"

class Player : public GameObject {
    World& world;
    std::string username;

public:
    // Constructor
    Player(World& world, const std::string& username);

    // Constructor y asignacion por copia deshabilitados
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    // Mueve el personaje segun la direccion dada
    void moveTo(int direction);

    // TODO: ...
    void update(int ms) override;
};

#endif // GAME_PLAYER_H
