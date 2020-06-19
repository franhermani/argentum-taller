#ifndef MEDITATE_COMMAND_DTO_H
#define MEDITATE_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class MeditateCommandDTO : public CommandDTO {
public:
    // Constructor
    MeditateCommandDTO();

    // Constructor y asignacion por copia deshabilitados
    MeditateCommandDTO(const MeditateCommandDTO&) = delete;
    MeditateCommandDTO& operator=(const MeditateCommandDTO&) = delete;

    // Destructor
    ~MeditateCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // MEDITATE_COMMAND_DTO_H
