#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>

class World;
class ClientHandler;
class ServerProtocol;

class Player {
    World& world;
    int id;
    int posX{}, posY{};
    bool isAlive;
    bool isMeditating;
    int orientation;            // TODO: crear enum
    int raceType;
    int classType;
    int bodyArmor;              // TODO: crear enum
    int headArmor;              // TODO: crear enum
    int weapon;                 // TODO: crear enum
    int actualLife, maxLife;
    int actualMana, maxMana;
    int actualGold, maxGold;
    int experience;
    int level;
//    Inventory inventory;

    // Genera posiciones iniciales aleatorias para el player
    void loadInitialPosition();

    // Resta puntos de vida al player
    void subtractLife(int life);

    friend class World;
    friend class ClientHandler;
    friend class ServerProtocol;

public:
    // Constructor
    Player(World& world, const int id);

    // Constructor y asignacion por copia deshabilitados
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    // TODO: ...
    void update(int ms);

    // Mueve el player segun la direccion dada
    void moveTo(int direction);

    // Recupera todos los puntos de vida y mana del player
    void heal();

    // Revive al player
    void revive();

    // El player entra en estado de meditacion
    void meditate();
};

#endif // GAME_PLAYER_H
