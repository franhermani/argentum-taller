#include <iostream>
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
    socket.sendBytes(message.c_str(), message.length());
}

const std::string ClientProtocol::receiveMessage() {
    // TODO: ...
    char buffer[BUF_MAX_SIZE];
    socket.receiveBytes(buffer, 10);
    buffer[10] = '\0';
    std::string str(buffer);
    std::cout << buffer << "\n";
    return buffer;
}
