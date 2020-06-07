#include "move_command.h"

MoveCommand::MoveCommand(const int direction) : direction(direction) {}

void MoveCommand::execute(Player& player) {
    player.moveTo(direction);
}
