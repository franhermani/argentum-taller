#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../../common/socket.h"
#include "../../common/commands/command.h"

class ClientProtocol {
    Socket& socket;

public:
    // Constructor
    explicit ClientProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    // Envia un comando a traves del socket
    void sendCommand(Command& command);
};

#endif // CLIENT_PROTOCOL_H
