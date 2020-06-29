#include <vector>
#include "priest.h"
#include "../../../common/defines/npcs.h"

Priest::Priest(const int pos_x, const int pos_y, const int orient) {
    type = PRIEST;
    posX = pos_x;
    posY = pos_y;
    orientation = orient;
}

Priest::~Priest() = default;

void Priest::revive(Player &player) {
    player.revive();
}

void Priest::heal(Player &player) {
    player.heal();
}

const std::vector<itemType> Priest::listItems() const {
    return std::vector<itemType>();
}
