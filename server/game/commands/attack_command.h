#ifndef ATTACK_COMMAND_H
#define ATTACK_COMMAND_H

#include "command.h"
#include "../player.h"

class AttackCommand : public Command {
    Player& player;
    uint16_t enemyId;

public:
    // Constructor
    AttackCommand(Player& player, const uint16_t enemy_id);

    // Constructor y asignacion por copia deshabilitados
    AttackCommand(const AttackCommand&) = delete;
    AttackCommand& operator=(const AttackCommand&) = delete;

    // Destructor
    ~AttackCommand() override;

    // Ataca al enemigo segun su 'enemyId'
    void execute() override;
};

#endif // ATTACK_COMMAND_H
