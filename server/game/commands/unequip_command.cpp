#include "unequip_command.h"

UnequipCommand::UnequipCommand(Player &player, const int unequip_type) :
        player(player), unequipType(unequip_type) {}

UnequipCommand::~UnequipCommand() = default;

void UnequipCommand::execute(World& world) {
    // TODO: ...
}
