#include "revive_command.h"
#include "../world.h"

ReviveCommand::ReviveCommand(Player& player) :
player(player) {}

ReviveCommand::ReviveCommand(Player& player, const uint16_t priest_pos_x,
        const uint16_t priest_pos_y) :
player(player), priestPosX(priest_pos_x), priestPosY(priest_pos_y) {}

ReviveCommand::~ReviveCommand() = default;

void ReviveCommand::execute(World& world) {
    if (priestPosX && priestPosY) {
        NPC* npc = world.getNPCByPos(position_t(priestPosX, priestPosY));
        npc->revive(player);
    } else {
        player.longTermRevive();
    }
}
