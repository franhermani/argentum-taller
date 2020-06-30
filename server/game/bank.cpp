#include "bank.h"
#include "game_exception.h"
#include "../../common/defines/game_exceptions.h"

Bank::Bank() {}

Bank::~Bank() {
    for (auto& player_id : itemsPerPlayer) {
        for (auto& item : player_id.second) {
            delete item;
        }
    }
}

void Bank::depositItem(const int id, Item *item) {
    std::unique_lock<std::mutex> lk(m);
    itemsPerPlayer[id].push_back(item);
}

Item* Bank::withdrawItem(const int id, const int type) {
    std::unique_lock<std::mutex> lk(m);

    if (itemsPerPlayer.find(id) == itemsPerPlayer.end())
        throw GameException(ITEM_NOT_IN_BANK);

    size_t i;
    for (i = 0; i < itemsPerPlayer[id].size(); i ++) {
        if (itemsPerPlayer[id][i]->type == type) {
            Item *item = itemsPerPlayer[id][i];
            itemsPerPlayer[id].erase(itemsPerPlayer[id].begin() + i);
            return item;
        }
    }
    throw GameException(ITEM_NOT_IN_BANK);
}

void Bank::depositGold(const int id, const int quant) {
    std::unique_lock<std::mutex> lk(m);

    if (goldPerPlayer.find(id) == goldPerPlayer.end())
        goldPerPlayer[id] = 0;

    goldPerPlayer[id] += quant;
}

const int Bank::withdrawGold(const int id, const int quant) {
    std::unique_lock<std::mutex> lk(m);

    if (goldPerPlayer.find(id) == goldPerPlayer.end())
        throw GameException(INSUFFICIENT_GOLD);

    if (quant > goldPerPlayer[id])
        throw GameException(INSUFFICIENT_GOLD);

    goldPerPlayer[id] -= quant;
    return quant;
}
