#include <vector>
#include <cstring>
#include "equip_command_dto.h"
#include "../../common/defines/commands.h"

EquipCommandDTO::EquipCommandDTO(const uint8_t item_type) :
itemType(item_type) {}

EquipCommandDTO::~EquipCommandDTO() = default;

const std::vector<char> EquipCommandDTO::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = sizeof(itemType);

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_EQUIP;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    byte_msg[2] = itemType;

    return byte_msg;
}
