#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include <vector>
#include "command.h"
#include "../entities/player.h"

class CommandFactory {
public:
    // Constructor
    CommandFactory();

    // Constructor y asignacion por copia deshabilitados
    CommandFactory(const CommandFactory& other) = delete;
    CommandFactory& operator=(const CommandFactory& other) = delete;

    // Recibe un commandType y sus argumentos y devuelve un Command*
    Command* operator()(Player& player, int type, std::vector<char>& arguments);
};


#endif // COMMAND_FACTORY_H
