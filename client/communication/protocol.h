#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include "../../common/protocol.h"
#include "../../common/socket.h"

class ClientProtocol : public Protocol {
    Socket& socket;

    // Codifica un mensaje segun el protocolo
    const char* encodeMessage(const std::string& message) override;

    // Decodifica un mensaje segun el protocolo
    const std::string decodeMessage(const char* message) override;

public:
    // Constructor
    explicit ClientProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    // Recibe un mensaje a traves del socket
    const std::string receiveMessage() override;

    // Envia un mensaje a traves del socket
    void sendMessage(const std::string& message) override;
};

#endif // CLIENT_PROTOCOL_H
