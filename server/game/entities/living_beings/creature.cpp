#include <random>
#include <vector>
#include <queue>
#include "creature.h"
#include "../../world.h"
#include "../../equations.h"
#include "../../../../common/defines/commands.h"
#include "../../../defines/creatures_death_drop.h"
#include "../../../../common/defines/attacks.h"

Creature::Creature(World &world, Equations& equations,
        const int new_id, const int type, const int new_level,
        const int move_velocity, const int attack_velocity,
        const int respawn_velocity) :
world(world),
equations(equations),
type(type),
attackRange(1),
moveVelocity(move_velocity),
attackVelocity(attack_velocity),
respawnVelocity(respawn_velocity),
msMoveCounter(0),
msRespawnCounter(0) {
    id = new_id;
    level = new_level;
    isAlive = true;
    orientation = DOWN;
    maxLife = equations.eqMaxLife(*this);
    actualLife = maxLife;
    pos = world.loadCreaturePosition();
}

Creature::~Creature() = default;

// --------------- //
// Private methods //
// --------------- //

std::queue<int> Creature::getMovementPriorities(position_t player_pos) {
    std::queue<int> priorities;
    int x_player = player_pos.x, y_player = player_pos.y;

    if (pos.x != x_player) {
        if (pos.x < x_player) {
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
        if (pos.y < y_player) {
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

position_t Creature::getMovementPosition(const int direction) {
    position_t new_pos = pos;

    switch (direction) {
        case LEFT:
            new_pos.x -= 1;
            break;
        case RIGHT:
            new_pos.x += 1;
            break;
        case DOWN:
            new_pos.y += 1;
            break;
        case UP:
            new_pos.y -= 1;
            break;
        default:
            break;
    }
    return new_pos;
}

void Creature::moveTo(position_t player_pos) {
    std::queue<int> tries_remaining = getMovementPriorities(player_pos);

    int direction = tries_remaining.front();
    tries_remaining.pop();

    position_t new_pos = getMovementPosition(direction);
    bool move_available = true;

    while ((! world.inMapBoundaries(new_pos)) ||
          (world.entityInCollision(new_pos))) {
        if (tries_remaining.empty()) {
            move_available = false;
            break;
        }
        direction = tries_remaining.front();
        tries_remaining.pop();
        new_pos = getMovementPosition(direction);
    }
    if (move_available) {
        pos = new_pos;
        orientation = direction;
    }
}

void Creature::die() {
    isAlive = false;
}

// TODO: enviarlos a un cementerio, no a una posicion aleatoria
void Creature::respawn() {
    dropItemOrGold();
    pos = world.loadCreaturePosition();
    isAlive = true;
}

void Creature::dropItemOrGold() {
    if (world.itemInCollision(pos))
        return;

    std::vector<int> death_drop = equations.eqCreatureDeathDrop(*this);
    int enum_drop = death_drop[0], param_drop = death_drop[1];

    switch (enum_drop) {
        case DROP_NOTHING:
            break;
        case DROP_GOLD:
            world.addGold(new Gold(param_drop, pos));
            break;
        case DROP_ITEM:
            world.addItem(param_drop, pos);
            break;
        default:
            break;
    }
}

void Creature::moveAndAttackPlayers() {
    position_t player_pos = world.getClosestPlayerPos(pos);
    bool in_attack_range = world.distanceInBlocks(
            pos, player_pos) <= attackRange;

    if (in_attack_range) {
        world.addAttack(new Attack(this, MELEE, pos,
                orientation, attackRange, attackVelocity));
    } else {
        moveTo(player_pos);
    }
}

// -------------- //
// Public methods //
// -------------- //

void Creature::update(int ms) {
    if (isDead()) {
        msRespawnCounter += ms;
        if (msRespawnCounter >= respawnVelocity) {
            msRespawnCounter = 0;
            respawn();
        }
    } else {
        msMoveCounter += ms;
        if (msMoveCounter >= moveVelocity) {
            msMoveCounter = 0;
            moveAndAttackPlayers();
        }
    }
}

void Creature::attack(Player& player) {
    if (isDead())
        return;

    player.receiveAttack(equations.eqDamageCaused(*this));
}

void Creature::attack(Creature &creature) {
    // Do nothing
}

const int Creature::receiveAttack(const int damage) {
    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}
