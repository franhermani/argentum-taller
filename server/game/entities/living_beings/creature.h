#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <queue>
#include "living_being.h"

class World;
class Player;
class Equations;

class Creature : public LivingBeing{
    World& world;
    Equations& equations;
    int type;
    int attackRange;
    int moveVelocity, attackVelocity;

    // Genera posiciones iniciales aleatorias para la criatura
    void loadInitialPosition();

    // TODO: ...
    void die() override;

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
    Creature(World& world, Equations& equations, const int new_id,
            const int type, const int new_level, const int move_velocity,
            const int attack_velocity);

    // Constructor y asignacion por copia deshabilitados
    Creature(const Creature& other) = delete;
    Creature& operator=(const Creature& other) = delete;

    // Destructor
    ~Creature();

    // Mueve a la criatura en busca de players para atacarlos
    void update(int ms) override;

    // Ataca a un player
    void attack(Player& player) override;

    // Ataca a una criatura
    // No hace nada
    void attack(Creature& creature) override;

    // Recibe el ataque de otro player
    // Devuelve la cantidad de daño realmente recibido
    const int receiveAttack(const int damage) override;
};

#endif // CREATURE_H
