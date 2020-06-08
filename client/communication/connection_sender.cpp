#include <string>
#include "connection_sender.h"
#include "../../common/socket_error.h"

ConnectionSender::ConnectionSender(Socket& socket) : protocol(socket),
keepTalking(true), isRunning(true), isFinished(false) {}

void ConnectionSender::run() {
    std::string message;

    while (keepTalking) {
        try {
            message = "Hola mundo";
            protocol.sendMessage(message);
        } catch(SocketError&) {
            break;
        }
    }
    isRunning = false;
}

void ConnectionSender::stop() {
    keepTalking = false;
}

bool ConnectionSender::isDead() {
    return (! isRunning);
}
