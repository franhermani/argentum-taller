#ifndef WITHDRAW_ITEM_COMMAND_H
#define WITHDRAW_ITEM_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class WithdrawItemCommand : public Command {
    Player& player;
    uint8_t itemType;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    WithdrawItemCommand(Player& player, const uint8_t item_type,
            const uint16_t banker_pos_x, const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    WithdrawItemCommand(const WithdrawItemCommand&) = delete;
    WithdrawItemCommand& operator=(const WithdrawItemCommand&) = delete;

    // Destructor
    ~WithdrawItemCommand() override;

    // Retira un item del banco y lo agrega al inventario
    void execute(World& world) override;
};

#endif // WITHDRAW_ITEM_COMMAND_H
