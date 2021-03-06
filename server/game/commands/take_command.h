#ifndef TAKE_COMMAND_H
#define TAKE_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class TakeCommand : public Command {
    Player& player;
    int takeType;
    int posX, posY;

public:
    // Constructor
    TakeCommand(Player& player, const int take_type,
            const int pos_x, const int pot_y);

    // Constructor y asignacion por copia deshabilitados
    TakeCommand(const TakeCommand&) = delete;
    TakeCommand& operator=(const TakeCommand&) = delete;

    // Destructor
    ~TakeCommand() override;

    // Toma un item del piso y lo equipa en el inventario
    void execute(World& world) override;
};

#endif // TAKE_COMMAND_H
