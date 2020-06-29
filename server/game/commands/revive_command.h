#ifndef REVIVE_COMMAND_H
#define REVIVE_COMMAND_H

#include "command.h"
#include "../player.h"

class ReviveCommand : public Command {
    Player& player;
    uint16_t priestId;

public:
    // Constructor sin sacerdote
    explicit ReviveCommand(Player& player);

    // Constructor con sacerdote
    ReviveCommand(Player& player, const uint16_t priest_id);

    // Constructor y asignacion por copia deshabilitados
    ReviveCommand(const ReviveCommand&) = delete;
    ReviveCommand& operator=(const ReviveCommand&) = delete;

    // Destructor
    ~ReviveCommand() override;

    // Revive al jugador
    void execute(World& world) override;
};

#endif // REVIVE_COMMAND_H
