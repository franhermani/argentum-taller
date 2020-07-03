#ifndef ATTACK_H
#define ATTACK_H

class Player;

class Attack {
    Player* player;
    int posX, posY;
    int direction;
    int range, blocksToRange;
    int moveVelocity;
    int msCounter;

    friend class World;

    void updatePosition();

public:
    // Constructor
    Attack(Player* player, const int pos_x, const int pos_y,
    const int direction, const int range, const int move_velocity);

    // Constructor y asignacion por copia deshabilitados
    Attack(const Attack& other) = delete;
    Attack& operator=(const Attack& other) = delete;

    // Actualiza la posicion del ataque segun 'ms'
    void update(const int ms);

    // Devuelve true si el ataque llego a su rango maximo
    const bool rangeReached() const;

    // Setea 'blocksToRange' en 0
    void collision();
};

#endif // ATTACK_H