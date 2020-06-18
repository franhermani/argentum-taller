#include "list_command.h"

ListCommand::ListCommand(Player& player, const uint16_t npc_id) :
player(player), npcId(npc_id) {}

ListCommand::~ListCommand() = default;

void ListCommand::execute() {
    // TODO: ...
}
