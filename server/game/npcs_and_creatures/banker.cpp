#include "banker.h"

Banker::Banker(const int pos_x, const int pos_y, const int orient) {
    posX = pos_x;
    posY = pos_y;
    orientation = orient;
}

Banker::~Banker() = default;

void Banker::depositItem(Player &player, int item_type) {
    // TODO: ...
}

void Banker::withdrawItem(Player &player, int item_type) {
    // TODO: ...
}

void Banker::depositGold(Player &player, int quantity) {
    // TODO: ...
}

void Banker::withdrawGold(Player &player, int quantity) {
    // TODO: ...
}
