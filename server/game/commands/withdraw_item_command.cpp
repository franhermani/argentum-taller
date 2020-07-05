#include "withdraw_item_command.h"
#include "../entities/npcs/banker.h"

WithdrawItemCommand::WithdrawItemCommand(Player &player, const int item_type,
        const uint16_t banker_pos_x, const uint16_t banker_pos_y) :
player(player), itemType(item_type),
bankerPosX(banker_pos_x), bankerPosY(banker_pos_y) {}

WithdrawItemCommand::~WithdrawItemCommand() = default;

void WithdrawItemCommand::execute(World& world) {
    auto* banker = dynamic_cast<Banker*>
            (world.getNPCByPos(bankerPosX, bankerPosY));
    banker->withdrawItem(player, itemType);
}
