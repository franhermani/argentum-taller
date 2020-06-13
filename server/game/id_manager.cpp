#include <string>
#include "id_manager.h"

#define FIRST_PLAYER_ID 1
#define LAST_PLAYER_ID  19999
#define FIRST_NPC_ID    20000
#define LAST_NPC_ID     39999
#define FIRST_ITEM_ID   40000
#define LAST_ITEM_ID    59999

IdManager::IdManager() : actual_player_id(FIRST_PLAYER_ID),
actual_npc_id(FIRST_NPC_ID), actual_item_id(FIRST_ITEM_ID) {}

const int IdManager::getPlayerByUsername(const std::string &username) {
    if (username_ids.find(username) == username_ids.end()) {
        if (actual_player_id == LAST_PLAYER_ID)
            throw NoMoreAvailableIdsException();
        username_ids[username] = ++actual_player_id;
    }
    return username_ids[username];
}

void IdManager::addNPCById() {
    if (actual_npc_id == LAST_NPC_ID) throw NoMoreAvailableIdsException();
    actual_npc_id ++;
}

void IdManager::addItemById() {
    if (actual_item_id == LAST_ITEM_ID) throw NoMoreAvailableIdsException();
    actual_item_id ++;
}
