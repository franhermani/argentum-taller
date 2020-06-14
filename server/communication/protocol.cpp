#include <iostream>
#include <string>
#include <vector>
#include "protocol.h"
#include "../../common/commands/defines.h"
#include "../../common/commands/move_command.h"

#define BYTE_SIZE 1
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

Command* ServerProtocol::receiveCommand() {
    char buffer1[BYTE_SIZE], buffer2[BYTE_SIZE];
    socket.receiveBytes(buffer1, BYTE_SIZE);
    socket.receiveBytes(buffer2, BYTE_SIZE);

    int type = buffer1[0];
    int length = buffer2[0];

    std::cout << type << "\n";
    std::cout << length << "\n";

    std::vector<char> arguments;
    arguments.resize(length);
    socket.receiveBytes(arguments.data(), arguments.size());

    if (type == CMD_MOVE) {
        return new MoveCommand(arguments[0]);
    } else {
        return nullptr;
    }
}
