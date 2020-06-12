#include "player.h"
#include "../commands/defines.h"

Player::Player(const World& world, const std::string &username) :
world(const_cast<World &>(world)), username(username) {}

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
    }
    if ((world.inMapBoundaries(new_x, new_y)) &&
        (! world.inCollision(new_x, new_y))) {
        posX = new_x;
        posY = new_y;
    }
}

void Player::update(int ms) {
    // TODO: ...
}
