#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include "../../common/protocol.h"
#include "../../common/socket.h"
#include "../../common/commands/command.h"

class ServerProtocol : public Protocol {
    Socket& socket;

    // Codifica un mensaje segun el protocolo
    const char* encodeMessage(const std::string& message) override;

    // Decodifica un mensaje segun el protocolo
    const std::string decodeMessage(const char* message) override;

public:
    // Constructor
    explicit ServerProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Recibe un mensaje a traves del socket
    const std::string receiveMessage() override;

    // Envia un mensaje a traves del socket
    void sendMessage(const std::string& message) override;

    // Recibe un comando a traves del socket
    // Devuelve un nuevo comando
    Command* receiveCommand();
};

#endif // SERVER_PROTOCOL_H
