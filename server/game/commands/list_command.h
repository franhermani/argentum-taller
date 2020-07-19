#ifndef LIST_COMMAND_H
#define LIST_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class ListCommand : public Command {
    Player& player;
    uint16_t NPCPosX, NPCPosY;

public:
    // Constructor
    explicit ListCommand(Player& player, const uint16_t npc_pos_x,
            const uint16_t npc_pos_y);

    // Constructor y asignacion por copia deshabilitados
    ListCommand(const ListCommand&) = delete;
    ListCommand& operator=(const ListCommand&) = delete;

    // Destructor
    ~ListCommand() override;

    // Lista los objetos del comerciante o banquero
    void execute(World& world) override;
};


#endif // LIST_COMMAND_H
