#ifndef ATTACK_COMMAND_H
#define ATTACK_COMMAND_H

#include <vector>
#include "command.h"

class AttackCommand : public Command {
    uint16_t enemyId;

public:
    // Constructor
    explicit AttackCommand(const uint16_t enemy_id);

    // Constructor y asignacion por copia deshabilitados
    AttackCommand(const AttackCommand&) = delete;
    AttackCommand& operator=(const AttackCommand&) = delete;

    // Destructor
    ~AttackCommand() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;

    // Ataca al enemigo segun su 'enemyId'
    void execute(Player& player) override;
};

#endif // ATTACK_COMMAND_H
