#include <string>
#include "protocol.h"

#define BUF_MAX_SIZE 1024

ServerProtocol::ServerProtocol(Socket& socket) : socket(socket) {}

void ServerProtocol::encodeMessage() {
    // TODO: ...
}

void ServerProtocol::decodeMessage() {
    // TODO: ...
}

void ServerProtocol::sendMessage(const std::string& message) {
    // TODO: ...
//    socket.sendBytes(message.c_str(), message.length());
}

const std::string ServerProtocol::receiveMessage() {
    // TODO: recibir en 2 bytes la longitud de todo el mensaje
//    char buffer[BUF_MAX_SIZE];
//    socket.receiveBytes(buffer, )
    std::string str = "Hola mundo\n";
    return str;
}
