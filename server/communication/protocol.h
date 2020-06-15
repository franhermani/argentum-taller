#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../../common/protocol.h"
#include "../../common/socket.h"
#include "../../common/commands/command.h"

class ServerProtocol : public Protocol {
    Socket& socket;

public:
    // Constructor
    explicit ServerProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Recibe un comando a traves del socket y devuelve un nuevo comando
    Command* receiveCommand() override;
};

#endif // SERVER_PROTOCOL_H
