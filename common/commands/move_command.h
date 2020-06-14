#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <vector>
#include "command.h"

class MoveCommand : public Command {
    int direction;

public:
    // Constructor
    explicit MoveCommand(const int direction);

    // Constructor y asignacion por copia deshabilitados
    MoveCommand(const MoveCommand&) = delete;
    MoveCommand& operator=(const MoveCommand&) = delete;

    // Destructor
    ~MoveCommand() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;

    // Mueve al personaje segun la direccion dada
    void execute(Player& player) override;
};

#endif // MOVE_COMMAND_H
