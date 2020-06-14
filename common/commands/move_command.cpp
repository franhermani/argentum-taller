#include <vector>
#include <cstring>
#include <netinet/in.h>
#include "move_command.h"
#include "defines.h"

MoveCommand::MoveCommand(const int direction) : direction(direction) {}

const std::vector<char> MoveCommand::serialize() const {
    // Longitud total
    uint8_t arguments_size = sizeof(moveDirection);
    int total_size = sizeof(commandType) + sizeof(uint16_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg.push_back(CMD_MOVE);

    // Longitud de los argumentos
    uint16_t length = htons(arguments_size);
    memcpy(&byte_msg.back(), &length, sizeof(length));

    // Argumentos
    byte_msg.push_back(direction);

    return byte_msg;
}

void MoveCommand::execute(Player& player) {
    // TODO: se queja el linkeo aca...
//    player.moveTo(direction);
}
