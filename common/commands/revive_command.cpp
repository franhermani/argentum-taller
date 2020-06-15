#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "revive_command.h"
#include "defines.h"

ReviveCommand::ReviveCommand() : priestId(0) {}

ReviveCommand::ReviveCommand(const uint16_t priest_id) : priestId(priest_id) {}

ReviveCommand::~ReviveCommand() = default;

const std::vector<char> ReviveCommand::serialize() const {
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

void ReviveCommand::execute(Player& player) {
    // TODO: ...
}
