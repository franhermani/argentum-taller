#include "bank.h"
#include "game_exception.h"

Bank::Bank(size_t max_items) : maxItemsPerPlayer(max_items) {}

Bank::~Bank() {
    for (auto& kv : itemsPerPlayer) {
        for (auto& item : kv.second) {
            delete item;
        }
    }
}

void Bank::depositItem(const int player_id, Item *item) {
    std::unique_lock<std::mutex> lk(m);
    if (itemsPerPlayer[player_id].size() == maxItemsPerPlayer)
        throw GameException(player_id, "No tienes mas espacio en el banco");

    itemsPerPlayer[player_id].push_back(item);
}

Item* Bank::withdrawItem(const int player_id, const int type) {
    std::unique_lock<std::mutex> lk(m);

    size_t i;
    for (i = 0; i < itemsPerPlayer[player_id].size(); i ++) {
        if (itemsPerPlayer[player_id][i]->type == type) {
            Item *item = itemsPerPlayer[player_id][i];
            itemsPerPlayer[player_id].erase(
                    itemsPerPlayer[player_id].begin() + i);
            return item;
        }
    }
    throw GameException(player_id, "No tienes este item en el banco");
}

void Bank::depositGold(const int player_id, const int quant) {
    std::unique_lock<std::mutex> lk(m);

    if (goldPerPlayer.find(player_id) == goldPerPlayer.end())
        goldPerPlayer[player_id] = 0;

    goldPerPlayer[player_id] += quant;
}

void Bank::withdrawGold(const int player_id, const int quant) {
    std::unique_lock<std::mutex> lk(m);

    if (goldPerPlayer.find(player_id) == goldPerPlayer.end() ||
            quant > goldPerPlayer[player_id])
        throw GameException(player_id, "No tienes %d de oro para "
                                       "extraer del banco", quant);

    goldPerPlayer[player_id] -= quant;
}

std::vector<Item*> Bank::getItems(const int player_id) {
    if (itemsPerPlayer.find(player_id) == itemsPerPlayer.end())
        return {};

    return itemsPerPlayer[player_id];
}

const int Bank::getGoldQuantity(const int player_id) {
    if (goldPerPlayer.find(player_id) == goldPerPlayer.end())
        return 0;

    return goldPerPlayer[player_id];
}
