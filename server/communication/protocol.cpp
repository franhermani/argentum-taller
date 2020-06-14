#include <iostream>
#include <string>
#include <vector>
#include "protocol.h"
#include "../../common/commands/defines.h"
#include "../../common/commands/move_command.h"
#include "../../common/commands/username_command.h"

#define BYTE_SIZE 1

ServerProtocol::ServerProtocol(Socket& socket) : socket(socket) {}

Command* ServerProtocol::receiveCommand() {
    char buffer1[BYTE_SIZE], buffer2[BYTE_SIZE];
    socket.receiveBytes(buffer1, BYTE_SIZE);
    socket.receiveBytes(buffer2, BYTE_SIZE);

    int type = buffer1[0];
    int length = buffer2[0];

    // DEBUG
    std::cout << type << "\n";
    std::cout << length << "\n";

    std::vector<char> arguments;
    arguments.resize(length);
    socket.receiveBytes(arguments.data(), arguments.size());

    if (type == CMD_USERNAME) {
        std::string username(arguments.begin(), arguments.end());
        // DEBUG
        std::cout << username << "\n";
        return new UsernameCommand(username);
    } else if (type == CMD_MEDITATE) {
        // TODO:...
    } else if (type == CMD_REVIVE) {
        // TODO:...
    } else if (type == CMD_HEAL) {
        // TODO:...
    } else if (type == CMD_DEPOSIT) {
        // TODO:...
    } else if (type == CMD_WITHDRAW) {
        // TODO:...
    } else if (type == CMD_LIST) {
        // TODO:...
    } else if (type == CMD_BUY) {
        // TODO:...
    } else if (type == CMD_SELL) {
        // TODO:...
    } else if (type == CMD_TAKE) {
        // TODO:...
    } else if (type == CMD_THROW) {
        // TODO:...
    } else if (type == CMD_MESSAGE) {
        // TODO:...
    } else if (type == CMD_MOVE) {
        int direction = arguments[0];
        return new MoveCommand(direction);
    } else if (type == CMD_ATTACK) {
        // TODO:...
    } else if (type == CMD_EQUIP) {
        // TODO:...
    } else if (type == CMD_TRICK) {
        // TODO:...
    }
    return nullptr;
}
