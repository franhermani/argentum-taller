#ifndef STOP_MOVE_COMMAND_H
#define STOP_MOVE_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class StopMoveCommand : public Command {
    Player& player;

public:
    // Constructor
    explicit StopMoveCommand(Player& player);

    // Constructor y asignacion por copia deshabilitados
    StopMoveCommand(const StopMoveCommand&) = delete;
    StopMoveCommand& operator=(const StopMoveCommand&) = delete;

    // Destructor
    ~StopMoveCommand() override;

    // Deja de mover al personaje
    void execute(World& world) override;
};

#endif // STOP_MOVE_COMMAND_H
