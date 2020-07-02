#include "attack.h"
#include "../../../common/defines/commands.h"

Attack::Attack(Player *player, const int pos_x, const int pos_y,
        const int direction, const int range, const double velocity) :
        player(player), posX(pos_x), posY(pos_y), direction(direction),
        range(range), blocksToRange(range), velocity(velocity) {}

void Attack::update(const int ms) {
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
    // TODO: actualizar posicion segun ms y velocity
    posX = new_x;
    posY = new_y;
}

const bool Attack::rangeReached() const {
    return blocksToRange == 0;
}

void Attack::collision() {
    blocksToRange = 0;
}
