#include <random>
#include "creature.h"
#include "../world.h"
#include "../equations.h"
#include "../player.h"
#include "../../../common/defines/commands.h"

Creature::Creature(World &world, Equations& equations,
        const int id, const int type) :
world(world),
equations(equations),
id(id),
type(type),
level(10),              // TODO: ver de donde cargar esto
isAlive(true),
orientation(DOWN),
maxLife(equations.eqMaxLife(*this)),
actualLife(maxLife) {
    loadInitialPosition();
}

// --------------- //
// Private methods //
// --------------- //

void Creature::loadInitialPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_x(0, world.getWidth() - 1);
    std::uniform_int_distribution<int> dist_y(0, world.getHeight() - 1);

    int new_x = dist_x(mt), new_y = dist_y(mt);
    while (world.inCollision(new_x, new_y)) {
        new_x = dist_x(mt);
        new_y = dist_y(mt);
    }
    posX = new_x;
    posY = new_y;
}

void Creature::moveTo(int direction) {
    int new_x = posX, new_y = posY;
    switch (direction) {
        case LEFT:
            new_x -= 1;
            break;
        case RIGHT:
            new_x += 1;
            break;
        case DOWN:
            new_y += 1;
            break;
        case UP:
            new_y -= 1;
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

void Creature::subtractLife(int life) {
    actualLife -= life;

    if (actualLife < 0)
        actualLife = 0;

    if (actualLife == 0)
        die();
}

void Creature::die() {
    isAlive = false;
    // TODO: dropear item u oro
    // TODO: respawnear en otra posicion (puede ser en un cementerio)
}

void Creature::attack(Player& player) {
    if (isDead())
        return;

    player.receiveAttack(equations.eqDamageCaused(*this));
}

// -------------- //
// Public methods //
// -------------- //

void Creature::update(int ms) {
    // TODO: moverse en busca de players y atacarlos
}

const int Creature::receiveAttack(const int damage) {
    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}

const bool Creature::isDead() const {
    return (! isAlive);
}
