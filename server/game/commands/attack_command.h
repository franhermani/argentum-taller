#ifndef ATTACK_COMMAND_H
#define ATTACK_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class AttackCommand : public Command {
    Player& player;
public:
    // Constructor
    explicit AttackCommand(Player& player);

    // Constructor y asignacion por copia deshabilitados
    AttackCommand(const AttackCommand&) = delete;
    AttackCommand& operator=(const AttackCommand&) = delete;

    // Destructor
    ~AttackCommand() override;

    // Ataca en la orientacion del player
    void execute(World& world) override;
};

#endif // ATTACK_COMMAND_H
