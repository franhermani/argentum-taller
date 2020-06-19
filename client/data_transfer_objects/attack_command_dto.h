#ifndef ATTACK_COMMAND_DTO_H
#define ATTACK_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class AttackCommandDTO : public CommandDTO {
    uint8_t enemyIdType;
    uint16_t enemyId;

public:
    // Constructor
    AttackCommandDTO(const uint8_t enemy_id_type, const uint16_t enemy_id);

    // Constructor y asignacion por copia deshabilitados
    AttackCommandDTO(const AttackCommandDTO&) = delete;
    AttackCommandDTO& operator=(const AttackCommandDTO&) = delete;

    // Destructor
    ~AttackCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // ATTACK_COMMAND_DTO_H
