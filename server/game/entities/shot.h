#ifndef SHOT_H
#define SHOT_H

class Player;

class Shot {
    Player& player;
    int posX, posY;
    int direction;
    double velocity;        // Blocks per second
    int range;              // Blocks
    bool outOfRange;

    // Actualiza la posicion (posX, posY) del shot
    void updatePosition(const int new_x, const int new_y);

public:
    // Constructor
    Shot(Player& player, const int pos_x, const int pos_y,
            const int direction, const double velocity,
            const int range);

    // Constructor y asignacion por copia deshabilitados
    Shot(const Shot& other) = delete;
    Shot& operator=(const Shot& other) = delete;

    // Actualiza la posicion del shot segun 'ms'
    void update(const int ms);

    // Setea la variable 'outOfRange' en true
    void disappear();
};

#endif // SHOT_H
