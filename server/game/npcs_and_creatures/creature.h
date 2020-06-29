#ifndef CREATURE_H
#define CREATURE_H

class World;

class Creature {
    World& world;
    int id;
    int type;
    int posX{}, posY{};
    int level;
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
    void attack(const int player_id);

public:
    Creature(World& world, const int id, const int type);

    // Constructor y asignacion por copia deshabilitados
    Creature(const Creature& other) = delete;
    Creature& operator=(const Creature& other) = delete;

    // TODO: ...
    void update(int ms);

    // Recibe el ataque de otro player
    // Devuelve la cantidad de daño realmente recibido
    const int receiveAttack(const int damage);
};

#endif // CREATURE_H
