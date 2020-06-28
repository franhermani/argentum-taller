#include "take_command.h"

TakeCommand::TakeCommand(Player& player, const int pos_x, const int pos_y) :
        player(player), posX(pos_x), posY(pos_y) {}

TakeCommand::~TakeCommand() = default;

void TakeCommand::execute() {
    player.takeItemFromWorldToInventory(posX, posY);
}
