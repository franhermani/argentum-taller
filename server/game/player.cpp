#include <random>
#include "player.h"
#include "world.h"
#include "../../common/commands/defines.h"

Player::Player(World& world, const int id) : world(world), id(id),
maxLife(100), actualLife(maxLife), orientation(DOWN) {
    loadInitialPosition();
    // TODO: maxLife sale de una ecuacion
}

void Player::loadInitialPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_x(0, world.getWidth());
    std::uniform_int_distribution<int> dist_y(0, world.getHeight());

    int new_x = dist_x(mt), new_y = dist_y(mt);
    while (world.inCollision(new_x, new_y)) {
        new_x = dist_x(mt);
        new_y = dist_y(mt);
    }
    posX = new_x;
    posY = new_y;
}

void Player::moveTo(int direction) {
    int new_x = posX, new_y = posY;
    switch (direction) {
        case LEFT:
            new_x -= 1;
            break;
        case RIGHT:
            new_x += 1;
            break;
        case DOWN:
            new_y -= 1;
            break;
        case UP:
            new_y += 1;
            break;
        default:
            break;
    }
    if ((world.inMapBoundaries(new_x, new_y)) &&
        (! world.inCollision(new_x, new_y))) {
        posX = new_x;
        posY = new_y;
    }
    orientation = direction;
}

void Player::update(int ms) {
    // TODO: ejecutar todas las acciones basadas en el tiempo
    // Por ejemplo, regenerar vida
}
