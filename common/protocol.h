#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include "commands/command.h"

class Protocol {
public:
    // Recibe un comando a traves del socket y devuelve un nuevo comando
    // Metodo a definir por las clases derivadas
    virtual Command* receiveCommand();

    // Envia un comando a traves del socket
    // Metodo a definir por las clases derivadas
    virtual void sendCommand(Command& command);
};

#endif // PROTOCOL_H
