#ifndef LIST_COMMAND_DTO_H
#define LIST_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class ListCommandDTO : public CommandDTO {
    uint16_t NPCPosX, NPCPosY;

public:
    // Constructor
    ListCommandDTO(const uint16_t npc_pos_x,
            const uint16_t npc_pos_y);

    // Constructor y asignacion por copia deshabilitados
    ListCommandDTO(const ListCommandDTO&) = delete;
    ListCommandDTO& operator=(const ListCommandDTO&) = delete;

    // Destructor
    ~ListCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};


#endif // LIST_COMMAND_DTO_H
