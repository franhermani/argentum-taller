#include <vector>
#include "merchant.h"
#include "../../../common/defines/npcs.h"

Merchant::Merchant(const int pos_x, const int pos_y, const int orient) {
    type = MERCHANT;
    posX = pos_x;
    posY = pos_y;
    orientation = orient;
}

Merchant::~Merchant() = default;

void Merchant::buy(Player &player, int item_type) {
    // TODO: ...
}

void Merchant::sell(Player &player, int item_type) {
    // TODO: ...
}

const std::vector<itemType> Merchant::listItems() const {
    // TODO: ...
    return std::vector<itemType>();
}
