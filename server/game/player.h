#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    std::string username;
    int posX;
    int posY;

public:
    // Constructor
    explicit Player(const std::string& username);

    // Mueve el personaje segun la direccion dada
    void moveTo(int direction);
};

#endif // PLAYER_H
