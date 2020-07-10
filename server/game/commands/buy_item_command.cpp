#include "buy_item_command.h"
#include "../world.h"

BuyItemCommand::BuyItemCommand(Player &player,
        const uint8_t item_type, const uint16_t npc_pos_x,
        const uint16_t npc_pos_y) :
player(player), itemType(item_type),
NPCPosX(npc_pos_x), NPCPosY(npc_pos_y) {}

BuyItemCommand::~BuyItemCommand() = default;

void BuyItemCommand::execute(World& world) {
    NPC* npc = world.getNPCByPos(position_t(NPCPosX, NPCPosY));
    npc->sellItem(player, itemType);
}
