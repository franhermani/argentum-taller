#ifndef WITHDRAW_GOLD_COMMAND_H
#define WITHDRAW_GOLD_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class WithdrawGoldCommand : public Command {
    Player& player;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    WithdrawGoldCommand(Player& player, const uint16_t banker_pos_x,
            const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    WithdrawGoldCommand(const WithdrawGoldCommand&) = delete;
    WithdrawGoldCommand& operator=(const WithdrawGoldCommand&) = delete;

    // Destructor
    ~WithdrawGoldCommand() override;

    // Retira oro del banco
    void execute(World& world) override;
};

#endif // WITHDRAW_GOLD_COMMAND_H
