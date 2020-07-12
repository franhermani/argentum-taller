#ifndef DEPOSIT_GOLD_COMMAND_H
#define DEPOSIT_GOLD_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class DepositGoldCommand : public Command {
    Player& player;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    DepositGoldCommand(Player& player, const uint16_t banker_pos_x,
            const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    DepositGoldCommand(const DepositGoldCommand&) = delete;
    DepositGoldCommand& operator=(const DepositGoldCommand&) = delete;

    // Destructor
    ~DepositGoldCommand() override;

    // Deposita el oro en exceso en el banco
    void execute(World& world) override;
};

#endif // DEPOSIT_GOLD_COMMAND_H
