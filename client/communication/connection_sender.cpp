#include <string>
#include "connection_sender.h"
#include "../../common/socket_error.h"
#include "../../common/commands/username_command.h"
#include "../../common/commands/meditate_command.h"
#include "../../common/commands/revive_command.h"
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

    ReviveCommand command(1234);
    protocol.sendCommand(command);

    isRunning = false;
}

void ConnectionSender::stop() {
    keepRunning = false;
}

bool ConnectionSender::isDead() {
    return (! isRunning);
}

void ConnectionSender::sendUsername(const std::string& username) {
    UsernameCommand usernameCommand(username);
    protocol.sendCommand(usernameCommand);
}
