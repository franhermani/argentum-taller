#include "list_exception.h"

ListException::ListException(const int player_id, list_t list) noexcept :
playerId(player_id), list(list) {}

const int ListException::getPlayerId() const noexcept {
    return playerId;
}

list_t ListException::getList() const noexcept {
    return list;
}
