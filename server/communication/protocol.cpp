#include <string>
#include "protocol.h"

ServerProtocol::ServerProtocol(Socket& socket) : socket(socket) {}

void ServerProtocol::encodeMessage() {
    // TODO: ...
}

void ServerProtocol::decodeMessage() {
    // TODO: ...
}

void ServerProtocol::sendMessage(const std::string& message) {
    // TODO: ...
}

const std::string ServerProtocol::receiveMessage() {
    // TODO: ...
    std::string str = "Hola mundo\n";
    return str;
}
