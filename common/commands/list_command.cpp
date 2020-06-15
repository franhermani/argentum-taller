#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "list_command.h"
#include "defines.h"

ListCommand::ListCommand(const uint16_t npc_id) : npcId(npc_id) {}

ListCommand::~ListCommand() = default;

const std::vector<char> ListCommand::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(npcId);

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_LIST;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    uint16_t id = htons(npcId);
    memcpy(&byte_msg[2], &id, arguments_size);

    return byte_msg;
}

void ListCommand::execute(Player& player) {
    // TODO: ...
}
