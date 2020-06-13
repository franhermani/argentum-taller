#include <iostream>
#include <string>
#include "protocol.h"

#define BUF_MAX_SIZE 1024

ServerProtocol::ServerProtocol(Socket& socket) : socket(socket) {}

const char* ServerProtocol::encodeMessage(const std::string& message) {
    // TODO: ...
    return "Hola mundo";
}

const std::string ServerProtocol::decodeMessage(const char* message) {
    // TODO: ...
    return "Hola mundo";
}

void ServerProtocol::sendMessage(const std::string& message) {
    // TODO: ...
    socket.sendBytes(message.c_str(), message.length());
}

const std::string ServerProtocol::receiveMessage() {
    // TODO: ...
    char buffer[BUF_MAX_SIZE];
    socket.receiveBytes(buffer, 11);
    buffer[11] = '\0';
    std::string str(buffer);
    std::cout << buffer << "\n";
    // TODO: decodeMessage(str);
    return buffer;
}
