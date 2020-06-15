#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../../common/protocol.h"
#include "../../common/socket.h"
#include "../../common/commands/command.h"
#include "../game/world.h"

class ServerProtocol : public Protocol {
    Socket& socket;

public:
    // Constructor
    explicit ServerProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Recibe un comando a traves del socket
    // Devuelve una clase derivada de Command
    Command* receiveCommand() override;

    // Envia el mapa a traves del socket
    // Recibe a Player para enviarle solo el mapa que lo rodea
    void sendMap(World& world, Player& player);
};

#endif // SERVER_PROTOCOL_H
