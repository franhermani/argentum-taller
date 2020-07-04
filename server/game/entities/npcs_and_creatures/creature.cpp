#include <random>
#include <vector>
#include <queue>
#include "creature.h"
#include "../../world.h"
#include "../../equations.h"
#include "../../../../common/defines/commands.h"
#include "../../../defines/creatures_death_drop.h"
#include "../items/potion.h"

Creature::Creature(World &world, Equations& equations,
        const int id, const int type, const int move_velocity,
        const int attack_velocity) :
world(world),
equations(equations),
id(id),
type(type),
level(10),              // TODO: ver de donde cargar esto
isAlive(true),
orientation(DOWN),
maxLife(equations.eqMaxLife(*this)),
actualLife(maxLife),
attackRange(1),
moveVelocity(move_velocity),
attackVelocity(attack_velocity),
msCounter(0) {
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

std::queue<int> Creature::getMovementPriorities(std::vector<int>& player_pos) {
    std::queue<int> priorities;
    int x_player = player_pos[0], y_player = player_pos[1];

    if (posX != x_player) {
        if (posX < x_player) {
            priorities.push(RIGHT);
            priorities.push(DOWN);
            priorities.push(UP);
            priorities.push(LEFT);
        } else {
            priorities.push(LEFT);
            priorities.push(DOWN);
            priorities.push(UP);
            priorities.push(RIGHT);
        }
    } else {
        if (posY < y_player) {
            priorities.push(DOWN);
            priorities.push(LEFT);
            priorities.push(RIGHT);
            priorities.push(UP);
        } else {
            priorities.push(UP);
            priorities.push(LEFT);
            priorities.push(RIGHT);
            priorities.push(DOWN);
        }
    }
    return priorities;
}

std::vector<int> Creature::getMovementPosition(const int direction) {
    std::vector<int> pos = {posX, posY};

    switch (direction) {
        case LEFT:
            pos[0] -= 1;
            break;
        case RIGHT:
            pos[0] += 1;
            break;
        case DOWN:
            pos[1] += 1;
            break;
        case UP:
            pos[1] -= 1;
            break;
        default:
            break;
    }
    return pos;
}

void Creature::moveTo(std::vector<int>& player_pos) {
    std::queue<int> tries_remaining = getMovementPriorities(player_pos);

    int direction = tries_remaining.front();
    tries_remaining.pop();

    std::vector<int> pos = getMovementPosition(direction);
    bool move_available = true;

    while ((! world.inMapBoundaries(pos[0], pos[1])) ||
           (world.inCollision(pos[0], pos[1]))) {
        if (tries_remaining.empty()) {
            move_available = false;
            break;
        }
        direction = tries_remaining.front();
        tries_remaining.pop();
        pos = getMovementPosition(direction);
    }
    if (move_available) {
        posX = pos[0];
        posY = pos[1];
        orientation = direction;
    }
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
    std::vector<int> death_drop = equations.eqCreatureDeathDrop(*this);

    int enum_drop = death_drop[0], param_drop = death_drop[1];

    switch (enum_drop) {
        case DROP_NOTHING:
            break;
        case DROP_GOLD:
            world.addGold(new Gold(param_drop, posX, posY));
            break;
        case DROP_POTION:
            world.addItem(param_drop, posX, posY);
            break;
        case DROP_ITEM:
            world.addItem(param_drop, posX, posY);
            break;
        default:
            break;
    }
    // TODO: respawnear en otra posicion (puede ser en un cementerio)
}

// -------------- //
// Public methods //
// -------------- //

void Creature::update(int ms) {
    msCounter += ms;

    if (msCounter < moveVelocity)
        return;

    msCounter = 0;
    std::vector<int> player_pos = world.getClosestPlayerPos(posX, posY);
    bool in_attack_range = world.distance(posX, posY,
            player_pos[0], player_pos[1]) <= attackRange;

    if (in_attack_range) {
//        world.addAttack(new Attack(...));
    } else {
        moveTo(player_pos);
    }
}

void Creature::attack(Player& player) {
    if (isDead())
        return;

    player.receiveAttack(equations.eqDamageCaused(*this));
}

const int Creature::receiveAttack(const int damage) {
    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}

const bool Creature::isDead() const {
    return (! isAlive);
}
