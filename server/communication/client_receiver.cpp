#include <string>
#include "client_receiver.h"
#include "../../common/socket_error.h"
#include "../game/commands/command.h"
#include "../game/commands/username_command.h"

ClientReceiver::ClientReceiver(Socket& socket,
        BlockingQueue<Command*>& command_queue) :
        protocol(socket), commandQueue(command_queue) {
    keepRunning = true;
    isRunning = true;
}

void ClientReceiver::run() {
    while (keepRunning) {
        try {
            Command* command = protocol.receiveCommand();
            commandQueue.push(command);
        } catch(SocketError&) {
            break;
        }
    }
    isRunning = false;
}

void ClientReceiver::stop() {
    keepRunning = false;
}

bool ClientReceiver::isDead() {
    return (! isRunning);
}

const std::string ClientReceiver::receiveUsername() {
    auto* command = dynamic_cast<UsernameCommand*>(protocol.receiveCommand());
//    std::string username = command->getUsername();
    delete command;
//    return username;
    return "franhermani";
}
