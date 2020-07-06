#include "list_command.h"
#include "../list_exception.h"

ListCommand::ListCommand(Player& player, const uint16_t npc_pos_x,
        const uint16_t npc_pos_y) :
player(player), NPCPosX(npc_pos_x), NPCPosY(npc_pos_y) {}

ListCommand::~ListCommand() = default;

void ListCommand::execute(World& world) {
    NPC* npc = world.getNPCByPos(NPCPosX, NPCPosY);
    throw ListException(player.id, npc->listItems(player));
}
