#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include "../../common/socket.h"
#include "../../common/data_transfer_objects/command_dto.h"
#include "../game/commands/command.h"
#include "../game/world_monitor.h"
#include "../game/commands/command_factory.h"

class ServerProtocol {
    Socket& socket;
    CommandFactory commandFactory;

public:
    // Constructor
    explicit ServerProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Recibe el username del cliente a traves del socket y lo devuelve
    const std::string receiveUsername();

    // Recibe un commandDTO del cliente a traves del socket
    // Llama al CommandFactory y devuelve una clase derivada de command
    Command* receiveCommand(Player& player);

    // Envia el mundo alrededor del player a traves del socket
    void sendWorldAround(WorldMonitor& world_monitor, Player& player);
};

#endif // SERVER_PROTOCOL_H
