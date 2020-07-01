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

void Banker::depositItem(Player &player, int type) {
    Item* item = player.takeItemFromInventory(type);
    bank.depositItem(player.id, item);
}

void Banker::withdrawItem(Player &player, int type) {
    Item* item = bank.withdrawItem(player.id, type);
    player.addItemToInventory(item);
}

void Banker::depositGold(Player &player, int quantity) {
    player.removeGold(quantity);
    bank.depositGold(player.id, quantity);
}

void Banker::withdrawGold(Player &player, int quantity) {
    bank.withdrawGold(player.id, quantity);
    player.addGold(quantity);
}

const std::vector<itemType> Banker::listItems() const {
    // TODO: ...
    return std::vector<itemType>();
}
