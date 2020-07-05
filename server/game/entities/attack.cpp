#include "attack.h"
#include "../../../common/defines/commands.h"

Attack::Attack(LivingBeing *owner, const int pos_x, const int pos_y,
        const int direction, const int range, const int move_velocity) :
        owner(owner), posX(pos_x), posY(pos_y), direction(direction),
        range(range), blocksToRange(range), isColliding(false),
        moveVelocity(move_velocity), msMoveCounter(0) {}

void Attack::updatePosition() {
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
    posX = new_x;
    posY = new_y;
    blocksToRange --;
}

void Attack::update(const int ms) {
    msMoveCounter += ms;

    if (msMoveCounter >= moveVelocity) {
        msMoveCounter = 0;
        updatePosition();
    }
}

const bool Attack::rangeReached() const {
    return blocksToRange == 0;
}

void Attack::collision() {
    blocksToRange = 0;
    isColliding = true;
}
