#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "heal_command.h"
#include "../defines/commands.h"

HealCommand::HealCommand(const uint16_t priest_id) : priestId(priest_id) {}

HealCommand::~HealCommand() = default;

const std::vector<char> HealCommand::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(priestId);

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

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

void HealCommand::execute(Player& player) {
    // TODO: ...
}
