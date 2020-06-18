#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "revive_command_dto.h"
#include "../defines/commands.h"

ReviveCommandDTO::ReviveCommandDTO() : priestId(0) {}

ReviveCommandDTO::ReviveCommandDTO(const uint16_t priest_id) :
priestId(priest_id) {}

ReviveCommandDTO::~ReviveCommandDTO() = default;

const std::vector<char> ReviveCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = (priestId > 0) ? sizeof(priestId) : 0;

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_REVIVE;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    if (arguments_size > 0) {
        uint16_t id = htons(priestId);
        memcpy(&byte_msg[2], &id, arguments_size);
    }
    return byte_msg;
}
