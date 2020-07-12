#include "withdraw_gold_command.h"
#include "../world.h"

WithdrawGoldCommand::WithdrawGoldCommand(Player &player,
        const uint16_t banker_pos_x, const uint16_t banker_pos_y) :
        player(player), bankerPosX(banker_pos_x), bankerPosY(banker_pos_y) {}

WithdrawGoldCommand::~WithdrawGoldCommand() = default;

void WithdrawGoldCommand::execute(World& world) {
    NPC* npc = world.getNPCByPos(position_t(bankerPosX, bankerPosY));
    npc->withdrawGold(player);
}
