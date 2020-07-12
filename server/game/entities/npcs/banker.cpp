#include <vector>
#include <netinet/in.h>
#include "banker.h"
#include "../../../../common/defines/npcs.h"
#include "../../game_exception.h"

Banker::Banker(Bank& bank, position_t new_pos, const int orient) : bank(bank) {
    type = BANKER;
    pos = new_pos;
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
    if (! item)
        return;

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

void Banker::depositGold(Player &player) {
    int excess_gold = player.removeExcessGold();
    bank.depositGold(player.id, excess_gold);
}

void Banker::withdrawGold(Player &player) {
    int safe_gold_space = player.getSafeGoldSpace();
    int gold_in_bank = bank.getGoldQuantity(player.id);
    int gold_to_extract = (gold_in_bank > safe_gold_space) ?
                           safe_gold_space : gold_in_bank;

    bank.withdrawGold(player.id, gold_to_extract);
    player.addGold(gold_to_extract);
}

list_t Banker::listItems(Player& player) const {
    std::vector<Item*> items = bank.getItems(player.id);
    int gold_quantity = bank.getGoldQuantity(player.id);

    int num_items = items.size();

    list_t list;
    list.show_price = 0;
    list.gold_quantity = htons(gold_quantity);
    list.num_items = htons(num_items);
    list.items.resize(num_items);

    int i;
    for (i = 0; i < num_items; i ++) {
        list.items[i].type = items[i]->type;
        list.items[i].price = items[i]->price;
    }
    return list;
}
