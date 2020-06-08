#include <string>
#include "client_receiver.h"
#include "../../common/socket_error.h"

ClientReceiver::ClientReceiver(Socket& socket) : protocol(socket),
        keepTalking(true), isRunning(true), isFinished(false) {}

void ClientReceiver::run() {
    std::string message;

    while (keepTalking) {
        try {
            message = protocol.receiveMessage();
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
