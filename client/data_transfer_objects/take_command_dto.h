#ifndef TAKE_COMMAND_DTO_H
#define TAKE_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class TakeCommandDTO : public CommandDTO {
    uint8_t takeType;
    uint16_t posX, posY;

public:
    // Constructor
    TakeCommandDTO(const uint8_t take_type, const uint16_t pos_x,
            const uint16_t pos_y);

    // Constructor y asignacion por copia deshabilitados
    TakeCommandDTO(const TakeCommandDTO&) = delete;
    TakeCommandDTO& operator=(const TakeCommandDTO&) = delete;

    // Destructor
    ~TakeCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // TAKE_COMMAND_DTO_H
