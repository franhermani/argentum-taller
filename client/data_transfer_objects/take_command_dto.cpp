#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "take_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_16      sizeof(uint16_t)

TakeCommandDTO::TakeCommandDTO(const uint16_t pos_x, const uint16_t pos_y) :
posX(pos_x), posY(pos_y) {}

TakeCommandDTO::~TakeCommandDTO() = default;

const std::vector<char> TakeCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(posX) + sizeof(posY);

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_TAKE;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    uint16_t pos_x = htons(posX), pos_y = htons(posY);
    memcpy(&byte_msg[2], &pos_x, SIZE_16);
    memcpy(&byte_msg[4], &pos_y, SIZE_16);

    return byte_msg;
}
