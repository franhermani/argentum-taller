#ifndef HEAL_COMMAND_H
#define HEAL_COMMAND_H

#include <vector>
#include "command.h"

class HealCommand : public Command {
    uint16_t priestId;

public:
    // Constructor
    explicit HealCommand(const uint16_t priest_id);

    // Constructor y asignacion por copia deshabilitados
    HealCommand(const HealCommand&) = delete;
    HealCommand& operator=(const HealCommand&) = delete;

    // Destructor
    ~HealCommand() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;

    // Recupera los puntos de vida y mana
    void execute(Player& player) override;
};

#endif // HEAL_COMMAND_H
