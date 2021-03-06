#ifndef DEPOSIT_ITEM_COMMAND_H
#define DEPOSIT_ITEM_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class DepositItemCommand : public Command {
    Player& player;
    uint8_t itemType;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    DepositItemCommand(Player& player, const uint8_t item_type,
            const uint16_t banker_pos_x, const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    DepositItemCommand(const DepositItemCommand&) = delete;
    DepositItemCommand& operator=(const DepositItemCommand&) = delete;

    // Destructor
    ~DepositItemCommand() override;

    // Retira un item del inventario y lo deposita en el banco
    void execute(World& world) override;
};

#endif // DEPOSIT_ITEM_COMMAND_H
