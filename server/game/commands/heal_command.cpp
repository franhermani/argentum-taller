#include "heal_command.h"
#include "../world.h"

HealCommand::HealCommand(Player& player, const uint16_t priest_pos_x,
        const uint16_t priest_pos_y) :
player(player), priestPosX(priest_pos_x), priestPosY(priest_pos_y) {}

HealCommand::~HealCommand() = default;

void HealCommand::execute(World& world) {
    NPC* npc = world.getNPCByPos(priestPosX, priestPosY);
    npc->heal(player);
}
