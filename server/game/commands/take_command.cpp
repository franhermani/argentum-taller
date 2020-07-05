#include "take_command.h"

TakeCommand::TakeCommand(Player& player, const int pos_x, const int pos_y) :
        player(player), posX(pos_x), posY(pos_y) {}

TakeCommand::~TakeCommand() = default;

void TakeCommand::execute(World& world) {
    // TODO: dos opciones para contemplar oros aca:
    // 1. Que el cliente envie un enum type en el command DTO
    // 2. Lanzar una exception si no se encuentra el item,
    // catchearla aca y buscar oros en posX, posY
    player.takeItemFromWorldToInventory(posX, posY);
}
