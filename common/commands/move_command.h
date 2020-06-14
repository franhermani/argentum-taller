#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "command.h"

class MoveCommand : public Command {
    int direction;

public:
    // Constructor
    explicit MoveCommand(const int direction);

    // Constructor y asignacion por copia deshabilitados
    MoveCommand(const MoveCommand&) = delete;
    MoveCommand& operator=(const MoveCommand&) = delete;

    // Mueve al personaje segun la direccion dada
    virtual void execute(Player& player) override;
};

#endif // MOVE_COMMAND_H
