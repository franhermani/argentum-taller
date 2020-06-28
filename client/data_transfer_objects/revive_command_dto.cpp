#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "revive_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_8      sizeof(uint8_t)
#define SIZE_16     sizeof(uint16_t)

ReviveCommandDTO::ReviveCommandDTO() = default;

ReviveCommandDTO::ReviveCommandDTO(const uint16_t priest_pos_x,
        const uint16_t priest_pos_y) :
priestPosX(priest_pos_x), priestPosY(priest_pos_y) {}

ReviveCommandDTO::~ReviveCommandDTO() = default;

const std::vector<char> ReviveCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = (priestPosX && priestPosY) ?
            sizeof(priestPosX) + sizeof(priestPosY) : 0;

    // Longitud total
    size_t total_size = 2 * SIZE_8 + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_REVIVE;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    if (arguments_size > 0) {
        uint16_t pos_x = htons(priestPosX), pos_y = htons(priestPosY);
        memcpy(&byte_msg[2], &pos_x, SIZE_16);
        memcpy(&byte_msg[4], &pos_y, SIZE_16);
    }
    return byte_msg;
}
