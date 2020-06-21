#include "heal_command.h"

HealCommand::HealCommand(Player& player, const uint16_t priest_id) :
player(player), priestId(priest_id) {}

HealCommand::~HealCommand() = default;

void HealCommand::execute() {
    player.heal();
}
