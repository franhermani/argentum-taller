#include <vector>
#include <queue>
#include "creature.h"
#include "../../world.h"
#include "../../equations.h"
#include "../../../../common/defines/commands.h"
#include "../../../defines/creatures_death_drop.h"
#include "../../../../common/defines/attacks.h"
#include "../../../../common/defines/sounds.h"


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
    orientation = DOWN;
    maxLife = equations.eqMaxLife(*this);
    actualLife = maxLife;
    state = STATE_NORMAL;
    pos = world.loadCreaturePosition();
}

Creature::~Creature() = default;

// --------------- //
// Private methods //
// --------------- //

void Creature::die() {
    state = STATE_DYING;
}

void Creature::respawn() {
    dropItemOrGold();
    pos = world.loadCreaturePositionInCemetery();
    state = STATE_NORMAL;
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
        orientTo(player_pos);
        attack();
    } else {
        moveTo(player_pos);
    }
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

void Creature::moveTo(position_t player_pos) {
    std::queue<int> tries_remaining = getMovementPriorities(player_pos);

    int direction = tries_remaining.front();
    tries_remaining.pop();

    position_t new_pos = getMovementPosition(direction);
    bool move_available = true;

    while ((! world.inMapBoundaries(new_pos)) ||
           (world.inSafePosition(new_pos)) ||
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

void Creature::orientTo(position_t player_pos) {
    int x_player = player_pos.x, y_player = player_pos.y;
    if (pos.x != x_player) {
        orientation = (pos.x < x_player) ? RIGHT : LEFT;
    } else {
        orientation = (pos.y < y_player) ? DOWN : UP;
    }
}

void Creature::attack() {
    position_t attack_pos = pos;

    switch (orientation) {
        case LEFT:
            attack_pos.x -= 1;
            break;
        case RIGHT:
            attack_pos.x += 1;
            break;
        case DOWN:
            attack_pos.y += 1;
            break;
        case UP:
            attack_pos.y -= 1;
            break;
        default:
            break;
    }

    world.addAttack(new Attack(this, MELEE, CREATURE_PUNCH,
            attack_pos, orientation, attackRange, attackVelocity));
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
    if (isDead())
        return 0;

    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}
