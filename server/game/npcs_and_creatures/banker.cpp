#include <vector>
#include "banker.h"
#include "../../../common/defines/npcs.h"

Banker::Banker(Bank& bank, const int pos_x, const int pos_y,
        const int orient) : bank(bank) {
    type = BANKER;
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

const std::vector<itemType> Banker::listItems() const {
    // TODO: ...
    return std::vector<itemType>();
}
