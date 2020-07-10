#ifndef UNEQUIP_COMMAND_DTO_H
#define UNEQUIP_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class UnequipCommandDTO : public CommandDTO {
    uint8_t unequipType;

public:
    // Constructor
    explicit UnequipCommandDTO(const uint8_t unequip_type);

    // Constructor y asignacion por copia deshabilitados
    UnequipCommandDTO(const UnequipCommandDTO&) = delete;
    UnequipCommandDTO& operator=(const UnequipCommandDTO&) = delete;

    // Destructor
    ~UnequipCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // UNEQUIP_COMMAND_DTO_H
