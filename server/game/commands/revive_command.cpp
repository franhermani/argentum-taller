#include "revive_command.h"
#include "../npcs_and_creatures/priest.h"

ReviveCommand::ReviveCommand(Player& player) :
player(player) {}

ReviveCommand::ReviveCommand(Player& player, const uint16_t priest_pos_x,
        const uint16_t priest_pos_y) :
player(player), priestPosX(priest_pos_x), priestPosY(priest_pos_y) {}

ReviveCommand::~ReviveCommand() = default;

void ReviveCommand::execute(World& world) {
    if (priestPosX && priestPosY) {
        auto* priest = dynamic_cast<Priest*>
        (world.getNPCByPos(priestPosX, priestPosY));
        priest->revive(player);
    } else {
        // TODO: inmovilizar al jugador
        player.revive();
    }
}
