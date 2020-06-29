#include "equip_command.h"

EquipCommand::EquipCommand(Player &player, const int item_type) :
player(player), itemType(item_type) {}

EquipCommand::~EquipCommand() = default;

void EquipCommand::execute(World& world) {
    player.equipItemFromInventory(itemType);
}
