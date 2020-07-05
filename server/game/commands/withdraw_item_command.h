#ifndef WITHDRAW_ITEM_COMMAND_H
#define WITHDRAW_ITEM_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class WithdrawItemCommand : public Command {
    Player& player;
    int itemType;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    WithdrawItemCommand(Player& player, const int item_type,
            const uint16_t banker_pos_x, const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    WithdrawItemCommand(const WithdrawItemCommand&) = delete;
    WithdrawItemCommand& operator=(const WithdrawItemCommand&) = delete;

    // Destructor
    ~WithdrawItemCommand() override;

    // Toma un objeto del inventario y lo tira al piso
    void execute(World& world) override;
};

#endif // WITHDRAW_ITEM_COMMAND_H
