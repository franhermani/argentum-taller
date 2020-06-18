#ifndef HEAL_COMMAND_H
#define HEAL_COMMAND_H

#include "command.h"
#include "../player.h"

class HealCommand : public Command {
    Player& player;
    uint16_t priestId;

public:
    // Constructor
    explicit HealCommand(Player& player, const uint16_t priest_id);

    // Constructor y asignacion por copia deshabilitados
    HealCommand(const HealCommand&) = delete;
    HealCommand& operator=(const HealCommand&) = delete;

    // Destructor
    ~HealCommand() override;

    // Recupera los puntos de vida y mana
    void execute() override;
};

#endif // HEAL_COMMAND_H
