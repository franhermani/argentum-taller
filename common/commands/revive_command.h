#ifndef REVIVE_COMMAND_H
#define REVIVE_COMMAND_H

#include <vector>
#include "command.h"

class ReviveCommand : public Command {
    uint16_t priestId;

public:
    // Constructor sin sacerdote
    ReviveCommand();

    // Constructor con sacerdote
    explicit ReviveCommand(const uint16_t priest_id);

    // Constructor y asignacion por copia deshabilitados
    ReviveCommand(const ReviveCommand&) = delete;
    ReviveCommand& operator=(const ReviveCommand&) = delete;

    // Destructor
    ~ReviveCommand() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;

    // Mueve al personaje segun la direccion dada
    void execute(Player& player) override;
};

#endif // REVIVE_COMMAND_H
