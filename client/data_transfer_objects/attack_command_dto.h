#ifndef ATTACK_COMMAND_DTO_H
#define ATTACK_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class AttackCommandDTO : public CommandDTO {
public:
    // Constructor
    AttackCommandDTO();

    // Constructor y asignacion por copia deshabilitados
    AttackCommandDTO(const AttackCommandDTO&) = delete;
    AttackCommandDTO& operator=(const AttackCommandDTO&) = delete;

    // Destructor
    ~AttackCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // ATTACK_COMMAND_DTO_H
