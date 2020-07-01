#include "bank.h"
#include "game_exception.h"

Bank::Bank() {}

Bank::~Bank() {
    for (auto& kv : itemsPerPlayer) {
        for (auto& item : kv.second) {
            delete item;
        }
    }
}

void Bank::depositItem(const int player_id, Item *item) {
    std::unique_lock<std::mutex> lk(m);
    itemsPerPlayer[player_id].push_back(item);
}

Item* Bank::withdrawItem(const int player_id, const int type) {
    std::unique_lock<std::mutex> lk(m);

    if (itemsPerPlayer.find(player_id) == itemsPerPlayer.end())
        throw GameException(player_id, "No tienes este item en el banco");

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
