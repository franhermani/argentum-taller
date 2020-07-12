#include <vector>
#include <cstring>
#include "unequip_command_dto.h"
#include "../../common/defines/commands.h"

#define SIZE_8      sizeof(uint8_t)

UnequipCommandDTO::UnequipCommandDTO(const uint8_t unequip_type) :
        unequipType(unequip_type) {}

UnequipCommandDTO::~UnequipCommandDTO() = default;

const std::vector<char> UnequipCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(unequipType);

    // Longitud total
    size_t total_size = 2 * SIZE_8 + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_UNEQUIP;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    byte_msg[2] = unequipType;

    return byte_msg;
}
