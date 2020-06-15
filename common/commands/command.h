#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include "../../server/game/player.h"

class Command {
public:
    // Destructor
    virtual ~Command();

    // Devuelve la serializacion en bytes del comando
    // Metodo a definir por las clases derivadas
    virtual const std::vector<char> serialize() const = 0;

    // Ejecuta el comando
    // Metodo a definir por las clases derivadas
    virtual void execute(Player& player);
};

#endif // COMMAND_H
