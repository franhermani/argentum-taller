#include <string>
#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket) : protocol(socket),
keepTalking(true), isRunning(true), isFinished(false) {}

void ClientSender::run() {
    std::string message;

    while (keepTalking) {
        try {
            message = "Hola mundo\n";
            protocol.sendMessage(message);
        } catch(SocketError) {
            break;
        }
    }
    isRunning = false;
}

void ClientSender::stop() {
    keepTalking = false;
}

const bool ClientSender::isDead() {
    return (! isRunning);
}
