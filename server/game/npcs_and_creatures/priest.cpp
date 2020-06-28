#include "priest.h"

Priest::Priest(const int pos_x, const int pos_y, const int orient) {
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
