#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket) : socket(socket),
keepTalking(true), isRunning(true), isFinished(false) {}

void ClientSender::run() {
    while (keepTalking) {
        try {
            // TODO: ...
            keepTalking = false;
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
