#ifndef SELL_ITEM_COMMAND_H
#define SELL_ITEM_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class SellItemCommand : public Command {
    Player& player;
    uint8_t itemType;
    uint16_t NPCPosX, NPCPosY;

public:
    // Constructor
    SellItemCommand(Player& player, const uint8_t item_type,
    const uint16_t npc_pos_x, const uint16_t npc_pos_y);

    // Constructor y asignacion por copia deshabilitados
    SellItemCommand(const SellItemCommand&) = delete;
    SellItemCommand& operator=(const SellItemCommand&) = delete;

    // Destructor
    ~SellItemCommand() override;

    // Saca un item del inventario y se lo vende al NPC
    void execute(World& world) override;
};

#endif // SELL_ITEM_COMMAND_H
