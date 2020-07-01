#include "attack_command.h"

AttackCommand::AttackCommand(Player& player) : player(player) {}

AttackCommand::~AttackCommand() = default;

void AttackCommand::execute(World& world) {
    // TODO: player.attack() --> codear de nuevo esta funcion
}
