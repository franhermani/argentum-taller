#include "sell_item_command.h"
#include "../entities/npcs/banker.h"

SellItemCommand::SellItemCommand(Player &player,
        const uint8_t item_type, const uint16_t npc_pos_x,
        const uint16_t npc_pos_y) :
player(player), itemType(item_type),
NPCPosX(npc_pos_x), NPCPosY(npc_pos_y) {}

SellItemCommand::~SellItemCommand() = default;

void SellItemCommand::execute(World& world) {
//    auto* banker = dynamic_cast<Banker*>
//    (world.getNPCByPos(bankerPosX, bankerPosY));
//    banker->withdrawItem(player, itemType);
}
