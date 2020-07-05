#ifndef BUY_ITEM_COMMAND_H
#define BUY_ITEM_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class BuyItemCommand : public Command {
    Player& player;
    uint8_t itemType;
    uint16_t NPCPosX, NPCPosY;

public:
    // Constructor
    BuyItemCommand(Player& player, const uint8_t item_type,
            const uint16_t npc_pos_x, const uint16_t npc_pos_y);

    // Constructor y asignacion por copia deshabilitados
    BuyItemCommand(const BuyItemCommand&) = delete;
    BuyItemCommand& operator=(const BuyItemCommand&) = delete;

    // Destructor
    ~BuyItemCommand() override;

    // Compra un item al NPC y lo agrega al inventario
    void execute(World& world) override;
};

#endif // BUY_ITEM_COMMAND_H
