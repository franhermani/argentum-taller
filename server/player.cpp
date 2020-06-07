#include "player.h"
#include "commands/defines.h"

Player::Player(const std::string &username) : username(username) {}

void Player::moveTo(int direction) {
    switch (direction) {
        // TODO: en todos chequear que no me fui del mapa
        case LEFT:
            // TODO: moverme hacia la izq en la matriz
            posX -= 1;
            break;
        case RIGHT:
            // TODO: moverme hacia la der en la matriz
            posX += 1;
            break;
        case UP:
            // TODO: moverme hacia arriba en la matriz
            posY += 1;
            break;
        case DOWN:
            // TODO: moverme hacia abajo en la matriz
            posY -= 1;
            break;
    }
}
