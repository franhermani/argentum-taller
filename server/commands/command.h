#ifndef COMMAND_H
#define COMMAND_H

#include "../player.h"

class Command {
public:
    // Metodo a definir por las clases derivadas
    virtual void execute(Player& player) = 0;
};

#endif // COMMAND_H
