#ifndef PUNCH_H
#define PUNCH_H

class Player;

class Punch {
    Player* player;
    int posX, posY;
    int direction;
    int range;              // Blocks (always 1)

    friend class World;

public:
    // Constructor
    Punch(Player* player, const int pos_x, const int pos_y,
            const int direction);

    // Constructor y asignacion por copia deshabilitados
    Punch(const Punch& other) = delete;
    Punch& operator=(const Punch& other) = delete;
};


#endif // PUNCH_H
