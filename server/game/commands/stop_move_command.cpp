#include "stop_move_command.h"

StopMoveCommand::StopMoveCommand(Player& player) : player(player) {}

StopMoveCommand::~StopMoveCommand() = default;

void StopMoveCommand::execute(World& world) {
    player.stopMoving();
}
