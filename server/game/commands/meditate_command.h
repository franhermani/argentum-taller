#ifndef MEDITATE_COMMAND_H
#define MEDITATE_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class MeditateCommand : public Command {
    Player& player;

public:
    // Constructor
    explicit MeditateCommand(Player& player);

    // Constructor y asignacion por copia deshabilitados
    MeditateCommand(const MeditateCommand&) = delete;
    MeditateCommand& operator=(const MeditateCommand&) = delete;

    // Destructor
    ~MeditateCommand() override;

    // Entra en estado de meditacion y recupera mana
    void execute(World& world) override;
};

#endif // MEDITATE_COMMAND_H
