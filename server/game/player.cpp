#include <random>
#include "player.h"
#include "world.h"
#include "../../common/defines/commands.h"

// TODO: estas inicializaciones salen de la clase de ecuaciones
Player::Player(World& world, const int id) :
world(world),
id(id),
isAlive(true),
isMeditating(false),
orientation(DOWN),
raceType(2),
classType(3),
bodyArmor(4),
headArmor(5),
weapon(6),
actualLife(100), maxLife(actualLife),
actualMana(200), maxMana(actualMana),
actualGold(300), maxGold(actualGold),
experience(400),
level(10) {
    loadInitialPosition();
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

void Player::update(int ms) {
    // TODO: llamar a la ecuacion que recupera vida
//    if (isMeditating) TODO: llamar a la ecuacion que recupera mana
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
    isMeditating = false;
}

void Player::subtractLife(int life) {
    actualLife -= life;
    if (actualLife < 0) actualLife = 0;
    if (actualLife == 0) isAlive = false;
    isMeditating = false;
}

void Player::heal() {
    actualLife = maxLife;
    actualMana = maxMana;
    isMeditating = false;
}

void Player::revive() {
    actualLife = maxLife;
    isAlive = true;
    isMeditating = false;
}

void Player::meditate() {
    isMeditating = true;
}
