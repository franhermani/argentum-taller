#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>

class World;
class ClientHandler;

class Player {
    World& world;
    int id;
    int maxLife, actualLife;
    int posX, posY;
    int orientation;

    // Genera posiciones iniciales aleatorias para el player
    void loadInitialPosition();

    friend class World;
    friend class ClientHandler;

public:
    // Constructor
    Player(World& world, const int id);

    // Constructor y asignacion por copia deshabilitados
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    // Mueve el player segun la direccion dada
    void moveTo(int direction);

    // TODO: ...
    void update(int ms);
};

#endif // GAME_PLAYER_H
