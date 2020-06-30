#ifndef CREATURE_H
#define CREATURE_H

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

    // Genera posiciones iniciales aleatorias para la criatura
    void loadInitialPosition();

    // Resta puntos de vida a la criatura
    void subtractLife(int life);

    // TODO: ...
    void die();

    // Mueve a la criatura segun la direccion dada
    void moveTo(int direction);

    // Ataca a otro player segun su ID
    void attack(Player& player);

    friend class World;
    friend class Equations;
    friend class ServerProtocol;

public:
    Creature(World& world, Equations& equations,
            const int id, const int type);

    // Constructor y asignacion por copia deshabilitados
    Creature(const Creature& other) = delete;
    Creature& operator=(const Creature& other) = delete;

    // TODO: ...
    void update(int ms);

    // Recibe el ataque de otro player
    // Devuelve la cantidad de daño realmente recibido
    const int receiveAttack(const int damage);

    // Devuelve true si esta muerto, false en caso contrario
    const bool isDead() const;
};

#endif // CREATURE_H
