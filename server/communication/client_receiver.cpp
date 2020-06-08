#include "client_receiver.h"
#include "../../common/socket_error.h"

ClientReceiver::ClientReceiver(Socket& socket) : socket(socket),
        keepTalking(true), isRunning(true), isFinished(false) {}

void ClientReceiver::run() {
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

void ClientReceiver::stop() {
    keepTalking = false;
}

const bool ClientReceiver::isDead() {
    return (! isRunning);
}
