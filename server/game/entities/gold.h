#ifndef GOLD_H
#define GOLD_H

class Gold {
    int quantity;
    int posX, posY;

    friend class World;
    friend class Player;

public:
    // Constructor
    Gold(const int quantity, const int pos_x, const int pos_y);

    // Constructor y asignacion por copia deshabilitados
    Gold(const Gold& other) = delete;
    Gold& operator=(const Gold& other) = delete;

    // Actualiza la posicion (posX, posY) del oro
    void updatePosition(const int new_x, const int new_y);
};

#endif // GOLD_H
