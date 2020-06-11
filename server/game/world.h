#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include "params.h"
#include "object.h"

class World {
    GameParams& params;
    // TODO: ver si es puntero o no
    std::vector<GameObject*> gameObjects;

public:
    // Constructor
    explicit World(GameParams& params);

    // Constructor y asignacion por copia deshabilitados
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;
};

#endif // GAME_WORLD_H
