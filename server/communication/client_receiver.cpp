#include <string>
#include "client_receiver.h"
#include "../../common/socket_error.h"
#include "../../common/commands/username_command.h"

ClientReceiver::ClientReceiver(Socket& socket) : protocol(socket) {
    keepRunning = true;
    isRunning = true;
}

void ClientReceiver::run() {
    while (keepRunning) {
        try {
            // TODO: el command tiene que encolarse y luego
            // gameManager lo desencola y lo ejecuta
//            Command* command = protocol.receiveCommand();
//            command->execute(*player);
//            delete command;
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
    std::string username = command->getUsername();
    delete command;
    return username;
}
