#include "deposit_gold_command.h"
#include "../entities/npcs/banker.h"

DepositGoldCommand::DepositGoldCommand(Player &player,
        const uint16_t quantity, const uint16_t banker_pos_x,
        const uint16_t banker_pos_y) :
player(player), quantity(quantity),
bankerPosX(banker_pos_x), bankerPosY(banker_pos_y) {}

DepositGoldCommand::~DepositGoldCommand() = default;

void DepositGoldCommand::execute(World& world) {
    NPC* npc = world.getNPCByPos(bankerPosX, bankerPosY);
    npc->depositGold(player, quantity);
}