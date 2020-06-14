#include <iostream>
#include <vector>
#include "move_command.h"
#include "defines.h"

MoveCommand::MoveCommand(const int direction) : direction(direction) {
    std::cout << direction << "\n";
}

MoveCommand::~MoveCommand() {}

const std::vector<char> MoveCommand::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(uint8_t);

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_MOVE;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    byte_msg[2] = direction;

    return byte_msg;
}

void MoveCommand::execute(Player& player) {
    // TODO: se queja el linkeo aca...
//    player.moveTo(direction);
}
