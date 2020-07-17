#include "attack.h"
#include "../../../common/defines/commands.h"

Attack::Attack(LivingBeing *owner, const int type, const int sound,
        position_t new_pos, const int direction, const int range,
        const int move_velocity) : owner(owner), type(type), sound(sound),
        pos(new_pos), direction(direction), range(range), blocksToRange(range),
        isColliding(false), moveVelocity(move_velocity), msMoveCounter(0) {}

void Attack::updatePosition() {
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
    pos = new_pos;
    blocksToRange --;
}

void Attack::update(const int ms) {
    msMoveCounter += ms;

    if (msMoveCounter >= moveVelocity) {
        msMoveCounter = 0;

        if (range == 1) {
            collision();
        } else {
            updatePosition();
        }
    }
}

const bool Attack::rangeReached() const {
    return blocksToRange == 0;
}

void Attack::collision() {
    blocksToRange = 0;
    isColliding = true;
}
