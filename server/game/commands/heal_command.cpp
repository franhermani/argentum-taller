#include "heal_command.h"

HealCommand::HealCommand(Player& player, const uint16_t priest_pos_x,
        const uint16_t priest_pos_y) :
player(player), priestPosX(priest_pos_x), priestPosY(priest_pos_y) {}

HealCommand::~HealCommand() = default;

void HealCommand::execute() {
    // TODO: obtener NPC de world por posX,posY y hacer npc.heal(player)
    player.heal();
}
