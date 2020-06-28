#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "heal_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_8      sizeof(uint8_t)
#define SIZE_16     sizeof(uint16_t)

HealCommandDTO::HealCommandDTO(const uint16_t priest_pos_x,
        const uint16_t priest_pos_y) :
priestPosX(priest_pos_x), priestPosY(priest_pos_y) {}

HealCommandDTO::~HealCommandDTO() = default;

const std::vector<char> HealCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(priestPosX) + sizeof(priestPosY);

    // Longitud total
    size_t total_size = 2 * SIZE_8 + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_HEAL;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    uint16_t pos_x = htons(priestPosX), pos_y = htons(priestPosY);
    memcpy(&byte_msg[2], &pos_x, SIZE_16);
    memcpy(&byte_msg[4], &pos_y, SIZE_16);

    return byte_msg;
}
