#include <vector>
#include "stop_move_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_8      sizeof(uint8_t)

StopMoveCommandDTO::StopMoveCommandDTO() = default;

StopMoveCommandDTO::~StopMoveCommandDTO() = default;

const std::vector<char> StopMoveCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = 0;

    // Longitud total
    size_t total_size = 2 * SIZE_8 + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_MOVE;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    return byte_msg;
}
