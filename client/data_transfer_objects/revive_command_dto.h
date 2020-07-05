#ifndef REVIVE_COMMAND_DTO_H
#define REVIVE_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class ReviveCommandDTO : public CommandDTO {
    uint16_t priestPosX{}, priestPosY{};

public:
    // Constructor sin sacerdote
    ReviveCommandDTO();

    // Constructor con sacerdote
    ReviveCommandDTO(const uint16_t priest_pos_x,
            const uint16_t priest_pos_y);

    // Constructor y asignacion por copia deshabilitados
    ReviveCommandDTO(const ReviveCommandDTO&) = delete;
    ReviveCommandDTO& operator=(const ReviveCommandDTO&) = delete;

    // Destructor
    ~ReviveCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // REVIVE_COMMAND_DTO_H
