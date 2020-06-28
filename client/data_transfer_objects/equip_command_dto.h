#ifndef EQUIP_COMMAND_DTO_H
#define EQUIP_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class EquipCommandDTO : public CommandDTO {
    uint8_t itemType;

public:
    // Constructor
    explicit EquipCommandDTO(const uint8_t item_type);

    // Constructor y asignacion por copia deshabilitados
    EquipCommandDTO(const EquipCommandDTO&) = delete;
    EquipCommandDTO& operator=(const EquipCommandDTO&) = delete;

    // Destructor
    ~EquipCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // EQUIP_COMMAND_DTO_H
