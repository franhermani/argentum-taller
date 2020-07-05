#ifndef WITHDRAW_ITEM_COMMAND_DTO_H
#define WITHDRAW_ITEM_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class WithdrawItemCommandDTO : public CommandDTO {
    uint8_t itemType;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    WithdrawItemCommandDTO(const uint8_t item_type,
            const uint16_t banker_pos_x, const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    WithdrawItemCommandDTO(const WithdrawItemCommandDTO&) = delete;
    WithdrawItemCommandDTO& operator=(const WithdrawItemCommandDTO&) = delete;

    // Destructor
    ~WithdrawItemCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // WITHDRAW_ITEM_COMMAND_DTO_H
