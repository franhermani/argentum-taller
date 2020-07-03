#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <queue>

class World;
class Player;
class Equations;

class Creature {
    World& world;
    Equations& equations;
    int id;
    int type;
    int posX{}, posY{};
    int level;
    bool isAlive;
    int orientation;
    int maxLife;
    int actualLife;
    int attackRange;
    int moveVelocity, attackVelocity;
    int msCounter;

    // Genera posiciones iniciales aleatorias para la criatura
    void loadInitialPosition();

    // Resta puntos de vida a la criatura
    void subtractLife(int life);

    // TODO: ...
    void die();

    // Devuelve la nueva pos (x,y) a la cual se moveria segun una direccion
    std::vector<int> getMovementPosition(const int direction);

    // Devuelve las direcciones a moverse para acercarse al player
    // en orden de conveniencia
    std::queue<int> getMovementPriorities(std::vector<int>& player_pos);

    // Mueve a la criatura
    void moveTo(std::vector<int>& player_pos);

    friend class World;
    friend class Equations;
    friend class ServerProtocol;

public:
    Creature(World& world, Equations& equations,
            const int id, const int type, const int move_velocity,
            const int attack_velocity);

    // Constructor y asignacion por copia deshabilitados
    Creature(const Creature& other) = delete;
    Creature& operator=(const Creature& other) = delete;

    // Mueve a la criatura en busca de players para atacarlos
    void update(int ms);

    // Ataca a un player
    void attack(Player& player);

    // Recibe el ataque de otro player
    // Devuelve la cantidad de daño realmente recibido
    const int receiveAttack(const int damage);

    // Devuelve true si esta muerto, false en caso contrario
    const bool isDead() const;
};

#endif // CREATURE_H
