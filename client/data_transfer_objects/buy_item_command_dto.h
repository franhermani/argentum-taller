#ifndef BUY_ITEM_COMMAND_DTO_H
#define BUY_ITEM_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class BuyItemCommandDTO : public CommandDTO {
    uint16_t itemType;
    uint16_t NPCPosX, NPCPosY;

public:
    // Constructor
    BuyItemCommandDTO(const uint8_t item_type,
            const uint16_t npc_pos_x, const uint16_t npc_pos_y);

    // Constructor y asignacion por copia deshabilitados
    BuyItemCommandDTO(const BuyItemCommandDTO&) = delete;
    BuyItemCommandDTO& operator=(const BuyItemCommandDTO&) = delete;

    // Destructor
    ~BuyItemCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // BUY_ITEM_COMMAND_DTO_H
