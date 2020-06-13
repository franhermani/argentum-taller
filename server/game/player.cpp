#include <iostream>
#include <random>
#include "player.h"
#include "../commands/defines.h"

Player::Player(World& world, const int id) :
world(world), id(id), orientation(DOWN) {
    // TODO: esto sale de una ecuacion
    loadInitialPosition();
    maxLife = 100;
    actualLife = maxLife;
    isImpenetrable = true;
}

void Player::loadInitialPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_x(0, world.getWidth());
    std::uniform_int_distribution<int> dist_y(0, world.getHeight());

    posX = dist_x(mt);
    posY = dist_y(mt);

//    std::cout << "Pos X: " << posX << "\n";
//    std::cout << "Pos Y: " << posY << "\n";
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
