#ifndef MEDITATE_COMMAND_H
#define MEDITATE_COMMAND_H

#include <vector>
#include "command.h"

class MeditateCommand : public Command {
public:
    // Constructor
    MeditateCommand();

    // Constructor y asignacion por copia deshabilitados
    MeditateCommand(const MeditateCommand&) = delete;
    MeditateCommand& operator=(const MeditateCommand&) = delete;

    // Destructor
    ~MeditateCommand() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;

    // Mueve al personaje segun la direccion dada
    void execute(Player& player) override;
};

#endif // MEDITATE_COMMAND_H
