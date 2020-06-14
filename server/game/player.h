#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include "living_object.h"

class World;

class Player : public LivingObject {
    World& world;
    int id;
    int orientation;

    // Genera posiciones iniciales aleatorias para el player
    void loadInitialPosition();

    friend class World;

public:
    // Constructor
    Player(World& world, const int id);

    // Constructor y asignacion por copia deshabilitados
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    // Mueve el player segun la direccion dada
    void moveTo(int direction) override;

    // TODO: ...
    void update(int ms) override;
};

#endif // GAME_PLAYER_H
