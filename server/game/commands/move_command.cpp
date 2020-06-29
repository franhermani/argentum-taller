#include "move_command.h"

MoveCommand::MoveCommand(Player& player, const int direction) :
player(player), direction(direction) {}

MoveCommand::~MoveCommand() = default;

void MoveCommand::execute(World& world) {
    player.moveTo(direction);
}
