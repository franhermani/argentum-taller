#ifndef LIST_EXCEPTION_H
#define LIST_EXCEPTION_H

#include <exception>
#include "entities/npcs/npc.h"

class ListException : public std::exception {
    int playerId;
    list_t list;

    friend class ServerProtocol;

public:
    ListException(const int player_id, list_t list) noexcept;

    // Devuelve el id del player
    const int getPlayerId() const noexcept;

    // Devuelve el struct list_t
    list_t getList() const noexcept;
};

#endif // LIST_EXCEPTION_H
