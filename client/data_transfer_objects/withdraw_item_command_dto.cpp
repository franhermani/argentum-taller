#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "withdraw_item_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_8      sizeof(uint8_t)
#define SIZE_16     sizeof(uint16_t)

WithdrawItemCommandDTO::WithdrawItemCommandDTO(const uint8_t item_type,
        const uint16_t banker_pos_x, const uint16_t banker_pos_y) :
itemType(item_type), bankerPosX(banker_pos_x),
bankerPosY(banker_pos_y) {}

WithdrawItemCommandDTO::~WithdrawItemCommandDTO() = default;

const std::vector<char> WithdrawItemCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(itemType) + sizeof(bankerPosX) +
                             sizeof(bankerPosY);

    // Longitud total
    size_t total_size = 2 * SIZE_8 + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_WITHDRAW_ITEM;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    uint16_t item_type = htons(itemType), pos_x = htons(bankerPosX),
             pos_y = htons(bankerPosY);

    memcpy(&byte_msg[2], &item_type, SIZE_8);
    memcpy(&byte_msg[3], &pos_x, SIZE_16);
    memcpy(&byte_msg[5], &pos_y, SIZE_16);

    return byte_msg;
}
