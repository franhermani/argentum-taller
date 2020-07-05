#include <vector>
#include "banker.h"
#include "../../../../common/defines/npcs.h"
#include "../../game_exception.h"

Banker::Banker(Bank& bank, const int pos_x, const int pos_y,
        const int orient) : bank(bank) {
    type = BANKER;
    posX = pos_x;
    posY = pos_y;
    orientation = orient;
}

Banker::~Banker() = default;

void Banker::revive(Player &player) {
    throw GameException(player.id, "Un banquero no tiene "
                                   "la habilidad de revivir al jugador");
}

void Banker::heal(Player &player) {
    throw GameException(player.id, "Un banquero no tiene "
                                   "la habilidad de curar al jugador");
}

void Banker::buyItem(Player &player, int type) {
    throw GameException(player.id, "Un banquero no puede "
                                   "comprar items");
}

void Banker::sellItem(Player &player, const int type) {
    throw GameException(player.id, "Un banquero no puede "
                                   "vender items");
}

void Banker::depositItem(Player &player, int type) {
    Item* item = player.takeItemFromInventory(type);
    bank.depositItem(player.id, item);
}

void Banker::withdrawItem(Player &player, int type) {
    Item* item = bank.withdrawItem(player.id, type);
    try {
        player.addItemToInventory(item);
    } catch (GameException& e) {
        depositItem(player, type);
        throw GameException(player.id, e.what());
    }
}

void Banker::depositGold(Player &player, int quantity) {
    player.removeGold(quantity);
    bank.depositGold(player.id, quantity);
}

void Banker::withdrawGold(Player &player, int quantity) {
    bank.withdrawGold(player.id, quantity);
    try {
        player.addGold(quantity);
    } catch (GameException& e) {
        depositGold(player, quantity);
        throw GameException(player.id, e.what());
    }
}

const std::vector<int> Banker::listItems() const {
    // TODO: ...
    return std::vector<int>();
}
