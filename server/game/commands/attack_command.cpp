#include "attack_command.h"

AttackCommand::AttackCommand(Player& player, const uint16_t enemy_id) :
player(player), enemyId(enemy_id) {}

AttackCommand::~AttackCommand() = default;

void AttackCommand::execute() {
    // TODO: ...
}
