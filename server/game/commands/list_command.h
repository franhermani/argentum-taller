#ifndef LIST_COMMAND_H
#define LIST_COMMAND_H

#include "command.h"
#include "../player.h"

class ListCommand : public Command {
    Player& player;
    uint16_t npcId;

public:
    // Constructor
    explicit ListCommand(Player& player, const uint16_t npc_id);

    // Constructor y asignacion por copia deshabilitados
    ListCommand(const ListCommand&) = delete;
    ListCommand& operator=(const ListCommand&) = delete;

    // Destructor
    ~ListCommand() override;

    // Lista los objetos del comerciante o banquero segun su 'npcId'
    void execute() override;
};


#endif // LIST_COMMAND_H
