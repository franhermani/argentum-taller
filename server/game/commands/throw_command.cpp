#include "throw_command.h"

ThrowCommand::ThrowCommand(Player &player, const int item_type) :
player(player), itemType(item_type) {}

ThrowCommand::~ThrowCommand() = default;

void ThrowCommand::execute() {
    player.dropItemFromInventoryToWorld(itemType);
}
