#ifndef MOVE_COMMAND_DTO_H
#define MOVE_COMMAND_DTO_H

#include <vector>
#include "command_dto.h"

class MoveCommandDTO : public CommandDTO {
    int direction;

public:
    // Constructor
    explicit MoveCommandDTO(const int direction);

    // Constructor y asignacion por copia deshabilitados
    MoveCommandDTO(const MoveCommandDTO&) = delete;
    MoveCommandDTO& operator=(const MoveCommandDTO&) = delete;

    // Destructor
    ~MoveCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // MOVE_COMMAND_DTO_H
