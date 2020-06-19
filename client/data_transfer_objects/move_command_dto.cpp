#include <vector>
#include "move_command_dto.h"
#include "../../common/defines/commands.h"

MoveCommandDTO::MoveCommandDTO(const int direction) : direction(direction) {}

MoveCommandDTO::~MoveCommandDTO() = default;

const std::vector<char> MoveCommandDTO::serialize() const {
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
