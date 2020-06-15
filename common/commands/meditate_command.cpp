#include <vector>
#include "meditate_command.h"
#include "defines.h"

MeditateCommand::MeditateCommand() = default;

MeditateCommand::~MeditateCommand() = default;

const std::vector<char> MeditateCommand::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = 0;

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_MEDITATE;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    return byte_msg;
}

void MeditateCommand::execute(Player& player) {
    // TODO: ...
}
