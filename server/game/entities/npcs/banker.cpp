#include <vector>
#include <netinet/in.h>
#include "banker.h"
#include "../../../../common/defines/npcs.h"
#include "../../../../common/defines/commands.h"
#include "../../game_exception.h"

Banker::Banker(Bank& bank, position_t new_pos) : bank(bank) {
    type = BANKER;
    pos = new_pos;
    orientation = DOWN;
}

Banker::~Banker() = default;

void Banker::revive(Player &player) {
    throw GameException(player.getId(), "Un banquero no tiene "
                                   "la habilidad de revivir al jugador");
}

void Banker::heal(Player &player) {
    throw GameException(player.getId(), "Un banquero no tiene "
                                   "la habilidad de curar al jugador");
}

void Banker::buyItem(Player &player, int type) {
    throw GameException(player.getId(), "Un banquero no puede "
                                   "comprar items");
}

void Banker::sellItem(Player &player, const int type) {
    throw GameException(player.getId(), "Un banquero no puede "
                                   "vender items");
}

void Banker::depositItem(Player &player, int type) {
    Item* item = player.takeItemFromInventory(type);
    if (! item)
        return;

    try {
        bank.depositItem(player.getId(), item);
    } catch (GameException& e) {
        player.addItemToInventory(item);
        throw e;
    }
}

void Banker::withdrawItem(Player &player, int type) {
    Item* item = bank.withdrawItem(player.getId(), type);
    try {
        player.addItemToInventory(item);
    } catch (GameException& e) {
        bank.depositItem(player.getId(), item);
        throw e;
    }
}

void Banker::depositGold(Player &player) {
    int excess_gold = player.removeExcessGold();
    bank.depositGold(player.getId(), excess_gold);
}

void Banker::withdrawGold(Player &player) {
    int safe_gold_space = player.getSafeGoldSpace();
    int gold_in_bank = bank.getGoldQuantity(player.getId());
    int gold_to_extract = (gold_in_bank > safe_gold_space) ?
                           safe_gold_space : gold_in_bank;

    bank.withdrawGold(player.getId(), gold_to_extract);
    player.addGold(gold_to_extract);
}

list_t Banker::listItems(Player& player) const {
    std::vector<Item*> items = bank.getItems(player.getId());
    int gold_quantity = bank.getGoldQuantity(player.getId());

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
