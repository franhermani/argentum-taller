#ifndef ATTACK_COMMAND_H
#define ATTACK_COMMAND_H

#include "command.h"
#include "../player.h"

class AttackCommand : public Command {
    Player& player;
    uint8_t enemyIdType;
    uint16_t enemyId;

public:
    // Constructor
    AttackCommand(Player& player, const uint8_t enemy_id_type,
            const uint16_t enemy_id);

    // Constructor y asignacion por copia deshabilitados
    AttackCommand(const AttackCommand&) = delete;
    AttackCommand& operator=(const AttackCommand&) = delete;

    // Destructor
    ~AttackCommand() override;

    // Ataca al enemigo segun su 'enemyId'
    void execute(World& world) override;
};

#endif // ATTACK_COMMAND_H
