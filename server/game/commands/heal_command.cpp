#include "heal_command.h"
#include "../npcs_and_creatures/priest.h"

HealCommand::HealCommand(Player& player, const uint16_t priest_pos_x,
        const uint16_t priest_pos_y) :
player(player), priestPosX(priest_pos_x), priestPosY(priest_pos_y) {}

HealCommand::~HealCommand() = default;

void HealCommand::execute(World& world) {
    auto* priest = dynamic_cast<Priest*>
            (world.getNPCByPos(priestPosX, priestPosY));

    priest->heal(player);
}
