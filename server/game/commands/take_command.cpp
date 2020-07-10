#include "take_command.h"
#include "../../../common/defines/commands.h"

TakeCommand::TakeCommand(Player& player, const int take_type,
        const int pos_x, const int pos_y) : player(player),
        takeType(take_type), posX(pos_x), posY(pos_y) {}

TakeCommand::~TakeCommand() = default;

void TakeCommand::execute(World& world) {
    switch (takeType) {
        case TAKE_ITEM:
            player.takeItemFromWorldToInventory(position_t(posX, posY));
            break;
        case TAKE_GOLD:
            player.takeGoldFromWorld(position_t(posX, posY));
            break;
        default:
            break;
    }
}
