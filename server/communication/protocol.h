#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <vector>
#include "../../common/socket.h"
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

    // Recibe la info del player del cliente a traves del socket
    const std::vector<char> receivePlayerInfo();

    // Envia un codigo de confirmacion del username al cliente
    void sendUsernameConfirmation(int code);

    // Recibe un commandDTO del cliente a traves del socket
    // Llama al CommandFactory y devuelve una clase derivada de command
    Command* receiveCommand(Player& player);

    // Envia la matriz de terrenos a traves del socket
    void sendMatrix(WorldMonitor& world_monitor);

    // Envia el mundo alrededor del player a traves del socket
    void sendWorldAround(WorldMonitor& world_monitor, Player& player);
};

#endif // SERVER_PROTOCOL_H
