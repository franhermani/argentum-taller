#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../../common/socket.h"
#include "../../common/commands/command.h"
#include "../game/world.h"

class ServerProtocol {
    Socket& socket;

public:
    // Constructor
    explicit ServerProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Recibe un comando a traves del socket
    // Devuelve una clase derivada de Command
    Command* receiveCommand();

    // Envia el mundo alrededor del player a traves del socket
    void sendWorldAround(World& world, Player& player);
};

#endif // SERVER_PROTOCOL_H
