#include <string>
#include <climits>
#include "id_manager.h"
#include "../../common/defines/username_confirmation.h"

IdManager::IdManager() : actual_player_id(1), actual_npc_id(1) {}

const int IdManager::addPlayerByUsername(const std::string &username) {
    if (username_ids.find(username) != username_ids.end())
        throw DuplicatedUsernameException();

    if (actual_player_id == USHRT_MAX)
        throw NoMoreAvailableIdsException();

    username_ids[username] = actual_player_id ++;
    return username_ids[username];
}

const int IdManager::addNPCById() {
    if (actual_npc_id == USHRT_MAX)
        throw NoMoreAvailableIdsException();

    actual_npc_id ++;
    return actual_npc_id;
}

void IdManager::removeUsername(const std::string& username) {
    username_ids.erase(username);
}

