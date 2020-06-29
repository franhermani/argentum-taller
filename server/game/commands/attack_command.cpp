#include "attack_command.h"
#include "../../../common/defines/id_types.h"

AttackCommand::AttackCommand(Player& player, const uint8_t enemy_id_type,
        const uint16_t enemy_id) : player(player), enemyIdType(enemy_id_type),
        enemyId(enemy_id) {}

AttackCommand::~AttackCommand() = default;

void AttackCommand::execute(World& world) {
    if (enemyIdType == ID_PLAYER) {
        Player* other = world.getPlayerById(enemyId);
        if (other) player.attack(*other);
    } else {
        Creature* creature = world.getCreatureById(enemyId);
        if (creature) player.attack(*creature);
    }
}
