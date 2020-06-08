#include "protocol.h"

#include <string>
#include "protocol.h"

#define BUF_MAX_SIZE 1024

ClientProtocol::ClientProtocol(Socket& socket) : socket(socket) {}

void ClientProtocol::encodeMessage() {
    // TODO: ...
}

void ClientProtocol::decodeMessage() {
    // TODO: ...
}

void ClientProtocol::sendMessage(const std::string& message) {
    // TODO: ...
//    socket.sendBytes(message.c_str(), message.length());
}

const std::string ClientProtocol::receiveMessage() {
    // TODO: recibir en 2 bytes la longitud de todo el mensaje
//    char buffer[BUF_MAX_SIZE];
//    socket.receiveBytes(buffer, )
    std::string str = "Hola mundo\n";
    return str;
}
