#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "heal_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_8      sizeof(uint8_t)

HealCommandDTO::HealCommandDTO(const uint16_t priest_id) :
priestId(priest_id) {}

HealCommandDTO::~HealCommandDTO() = default;

const std::vector<char> HealCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(priestId);

    // Longitud total
    size_t total_size = 2 * SIZE_8 + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_HEAL;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    uint16_t id = htons(priestId);
    memcpy(&byte_msg[2], &id, arguments_size);

    return byte_msg;
}
