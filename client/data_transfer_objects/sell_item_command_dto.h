#ifndef SELL_ITEM_COMMAND_DTO_H
#define SELL_ITEM_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class SellItemCommandDTO : public CommandDTO {
    uint16_t itemType;
    uint16_t NPCPosX, NPCPosY;

public:
    // Constructor
    SellItemCommandDTO(const uint8_t item_type,
            const uint16_t npc_pos_x, const uint16_t npc_pos_y);

    // Constructor y asignacion por copia deshabilitados
    SellItemCommandDTO(const SellItemCommandDTO&) = delete;
    SellItemCommandDTO& operator=(const SellItemCommandDTO&) = delete;

    // Destructor
    ~SellItemCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};


#endif // SELL_ITEM_COMMAND_DTO_H
