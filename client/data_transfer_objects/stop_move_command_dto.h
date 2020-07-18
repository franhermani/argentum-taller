#ifndef STOP_MOVE_COMMAND_DTO_H
#define STOP_MOVE_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class StopMoveCommandDTO : public CommandDTO {
public:
    // Constructor
    StopMoveCommandDTO();

    // Constructor y asignacion por copia deshabilitados
    StopMoveCommandDTO(const StopMoveCommandDTO&) = delete;
    StopMoveCommandDTO& operator=(const StopMoveCommandDTO&) = delete;

    // Destructor
    ~StopMoveCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // STOP_MOVE_COMMAND_DTO_H
