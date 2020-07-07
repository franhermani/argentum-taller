#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include "sell_item_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_8      sizeof(uint8_t)
#define SIZE_16     sizeof(uint16_t)

SellItemCommandDTO::SellItemCommandDTO(const uint8_t item_type,
        const uint16_t npc_pos_x, const uint16_t npc_pos_y) :
itemType(item_type), NPCPosX(npc_pos_x),
NPCPosY(npc_pos_y) {}

SellItemCommandDTO::~SellItemCommandDTO() = default;

const std::vector<char> SellItemCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(itemType) + sizeof(NPCPosX) +
                             sizeof(NPCPosY);

    // Longitud total
    size_t total_size = 2 * SIZE_8 + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_SELL;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    uint8_t item_type = itemType;
    uint16_t pos_x = htons(NPCPosX),
             pos_y = htons(NPCPosY);

    memcpy(&byte_msg[2], &item_type, SIZE_8);
    memcpy(&byte_msg[3], &pos_x, SIZE_16);
    memcpy(&byte_msg[5], &pos_y, SIZE_16);

    return byte_msg;
}
