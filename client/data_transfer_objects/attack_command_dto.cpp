#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "attack_command_dto.h"
#include "../../common/defines/commands.h"

AttackCommandDTO::AttackCommandDTO(const uint8_t enemy_id_type,
        const uint16_t enemy_id) : enemyIdType(enemy_id_type),
        enemyId(enemy_id) {}

AttackCommandDTO::~AttackCommandDTO() = default;

const std::vector<char> AttackCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(enemyIdType) + sizeof(enemyId);

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_ATTACK;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    byte_msg[2] = enemyIdType;
    uint16_t id = htons(enemyId);
    memcpy(&byte_msg[3], &id, arguments_size);

    return byte_msg;
}
