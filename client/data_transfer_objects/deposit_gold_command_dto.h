#ifndef DEPOSIT_GOLD_COMMAND_DTO_H
#define DEPOSIT_GOLD_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class DepositGoldCommandDTO : public CommandDTO {
    uint16_t bankerPosX, bankerPosY;

public:
    // Constructor
    DepositGoldCommandDTO(const uint16_t banker_pos_x,
            const uint16_t banker_pos_y);

    // Constructor y asignacion por copia deshabilitados
    DepositGoldCommandDTO(const DepositGoldCommandDTO&) = delete;
    DepositGoldCommandDTO& operator=(const DepositGoldCommandDTO&) = delete;

    // Destructor
    ~DepositGoldCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // DEPOSIT_GOLD_COMMAND_DTO_H
