#ifndef ATTACK_H
#define ATTACK_H

#include "../../../common/utilities/position.hpp"

class LivingBeing;

class Attack {
    LivingBeing* owner;
    int type;
    int sound;
    position_t pos;
    int direction;
    int range, blocksToRange;
    bool isColliding;
    int moveVelocity;
    int msMoveCounter;

    friend class World;
    friend class ServerProtocol;

    void updatePosition();

public:
    // Constructor
    Attack(LivingBeing* owner, const int type, const int sound,
            position_t new_pos, const int direction, const int range,
            const int move_velocity);

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
