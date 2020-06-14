#include <string>
#include "connection_sender.h"
#include "../../common/socket_error.h"
#include "../../common/commands/move_command.h"

ConnectionSender::ConnectionSender(Socket& socket) : protocol(socket) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionSender::run() {
    /*
    std::string message;

    while (keepRunning) {
        try {
            // TODO: recibir un comando del InputHandler y enviarlo
            message = "Hola mundo";
            protocol.sendMessage(message);
        } catch(SocketError&) {
            break;
        }
    }
     */

    MoveCommand moveCommand(1);
    protocol.sendCommand(moveCommand);

    isRunning = false;
}

void ConnectionSender::stop() {
    keepRunning = false;
}

bool ConnectionSender::isDead() {
    return (! isRunning);
}

void ConnectionSender::sendUsername(const std::string& username) {
//    protocol.sendMessage(username);
//    std::cout << username << "\n";
}
