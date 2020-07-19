#include <string>
#include <climits>
#include "id_manager.h"
#include "../../common/defines/username_codes.h"

IdManager::IdManager() : actual_player_id(1), actual_creature_id(1) {}

const int IdManager::addPlayerByUsername(const std::string &username) {
    if (username_ids.find(username) != username_ids.end())
        throw DuplicatedUsernameException();

    if (actual_player_id == USHRT_MAX)
        throw NoMoreAvailableIdsException();

    username_ids[username] = actual_player_id ++;
    return username_ids[username];
}

const int IdManager::addCreatureById() {
    if (actual_creature_id == USHRT_MAX)
        throw NoMoreAvailableIdsException();

    actual_creature_id ++;
    return actual_creature_id;
}

void IdManager::removeUsername(const std::string& username) {
    username_ids.erase(username);
}
