#include <string>
#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket) : protocol(socket) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    /*
    std::string message;

    while (keepRunning) {
        try {
            // TODO: recibo el mapa y actualizo el modelo local
            message = protocol.receiveMessage();
        } catch(SocketError&) {
            break;
        }
    }
     */
    isRunning = false;
}

void ConnectionReceiver::stop() {
    keepRunning = false;
}

bool ConnectionReceiver::isDead() {
    return (! isRunning);
}
