#ifndef HEAL_COMMAND_DTO_H
#define HEAL_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class HealCommandDTO : public CommandDTO {
    uint16_t priestId;

public:
    // Constructor
    explicit HealCommandDTO(const uint16_t priest_id);

    // Constructor y asignacion por copia deshabilitados
    HealCommandDTO(const HealCommandDTO&) = delete;
    HealCommandDTO& operator=(const HealCommandDTO&) = delete;

    // Destructor
    ~HealCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // HEAL_COMMAND_DTO_H
