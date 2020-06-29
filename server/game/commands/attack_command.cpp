#include "attack_command.h"

AttackCommand::AttackCommand(Player& player, const uint8_t enemy_id_type,
        const uint16_t enemy_id) : player(player), enemyIdType(enemy_id_type),
        enemyId(enemy_id) {}

AttackCommand::~AttackCommand() = default;

void AttackCommand::execute(World& world) {
    // TODO: ver si conviene obtener el enemigo de world
    player.attack(enemyIdType, enemyId);
}
