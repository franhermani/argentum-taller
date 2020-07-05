#ifndef DEPOSIT_ITEM_COMMAND_DTO_H
#define DEPOSIT_ITEM_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class DepositItemCommandDTO : public CommandDTO {
    uint8_t itemType;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    DepositItemCommandDTO(const uint8_t item_type,
            const uint16_t banker_pos_x, const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    DepositItemCommandDTO(const DepositItemCommandDTO&) = delete;
    DepositItemCommandDTO& operator=(const DepositItemCommandDTO&) = delete;

    // Destructor
    ~DepositItemCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // DEPOSIT_ITEM_COMMAND_DTO_H
