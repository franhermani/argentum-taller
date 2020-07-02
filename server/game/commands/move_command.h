#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "command.h"
#include "../entities/player.h"

class MoveCommand : public Command {
    Player& player;
    int direction;

public:
    // Constructor
    MoveCommand(Player& player, const int direction);

    // Constructor y asignacion por copia deshabilitados
    MoveCommand(const MoveCommand&) = delete;
    MoveCommand& operator=(const MoveCommand&) = delete;

    // Destructor
    ~MoveCommand() override;

    // Mueve al personaje segun 'direction'
    void execute(World& world) override;
};

#endif // MOVE_COMMAND_H
