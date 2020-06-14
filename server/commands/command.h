#ifndef COMMAND_H
#define COMMAND_H

#include "../game/player.h"

class Command {
public:
    // Devuelve el tipo del comando
    // Metodo a definir por las clases derivadas
    virtual void getType() const = 0;

    // Devuelve la longitud del mensaje a enviar por sockets
    // Metodo a definir por las clases derivadas
    virtual void getMessageLength() const = 0;

    // Devuelve los argumentos del mensaje a enviar por sockets
    // Metodo a definir por las clases derivadas
    virtual void getArguments() const = 0;

    // Ejecuta el comando
    // Metodo a definir por las clases derivadas
    virtual void execute(Player& player) = 0;
};

#endif // COMMAND_H
