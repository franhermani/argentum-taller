#include <string>
#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket) : protocol(socket),
keepTalking(true), isRunning(true), isFinished(false) {}

void ConnectionReceiver::run() {
    std::string message;

    while (keepTalking) {
        try {
            message = protocol.receiveMessage();
        } catch(SocketError&) {
            break;
        }
    }
    isRunning = false;
}

void ConnectionReceiver::stop() {
    keepTalking = false;
}

bool ConnectionReceiver::isDead() {
    return (! isRunning);
}
