#ifndef THROW_COMMAND_DTO_H
#define THROW_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class ThrowCommandDTO : public CommandDTO {
    uint8_t itemType;

public:
    // Constructor
    explicit ThrowCommandDTO(const uint8_t item_type);

    // Constructor y asignacion por copia deshabilitados
    ThrowCommandDTO(const ThrowCommandDTO&) = delete;
    ThrowCommandDTO& operator=(const ThrowCommandDTO&) = delete;

    // Destructor
    ~ThrowCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // THROW_COMMAND_DTO_H
