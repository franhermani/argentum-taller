#ifndef WITHDRAW_GOLD_COMMAND_DTO_H
#define WITHDRAW_GOLD_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class WithdrawGoldCommandDTO : public CommandDTO {
    uint16_t quantity;
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    WithdrawGoldCommandDTO(const uint16_t quantity,
            const uint16_t banker_pos_x, const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    WithdrawGoldCommandDTO(const WithdrawGoldCommandDTO&) = delete;
    WithdrawGoldCommandDTO& operator=(const WithdrawGoldCommandDTO&) = delete;

    // Destructor
    ~WithdrawGoldCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};


#endif // WITHDRAW_GOLD_COMMAND_DTO_H
