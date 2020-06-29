#include "revive_command.h"

ReviveCommand::ReviveCommand(Player& player) :
player(player), priestId(0) {}

ReviveCommand::ReviveCommand(Player& player, const uint16_t priest_id) :
player(player), priestId(priest_id) {}

ReviveCommand::~ReviveCommand() = default;

void ReviveCommand::execute(World& world) {
    player.revive();
}
