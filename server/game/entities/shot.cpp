#include "shot.h"

Shot::Shot(Player &player, const int direction, const double velocity,
        const int range) : player(player), velocity(velocity),
        range(range), outOfRange(false) {}

void Shot::updatePosition(const int new_x, const int new_y) {
    posX = new_x;
    posY = new_y;
}

void Shot::update(const int ms) {
    // TODO: actualizar posicion y chequear colision
}

void Shot::disappear() {
    outOfRange = true;
}
