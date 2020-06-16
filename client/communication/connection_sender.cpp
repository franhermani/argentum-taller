#include <string>
#include "connection_sender.h"
#include "../../common/socket_error.h"
#include "../../common/commands/username_command.h"
#include "../../common/commands/attack_command.h"

ConnectionSender::ConnectionSender(Socket& socket,
        BlockingQueue<Command*>& commandQueue) : protocol(socket), commandQueue(commandQueue) {
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

    AttackCommand command(27500);
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
