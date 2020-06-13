#include <string>
#include "client_receiver.h"
#include "../../common/socket_error.h"

ClientReceiver::ClientReceiver(Socket& socket) : protocol(socket) {
    keepRunning = true;
    isRunning = true;
}

void ClientReceiver::run() {
    /*
    std::string message;

    while (keepRunning) {
        try {
            // TODO: recibir un comando del client y actualizar el mapa
            message = protocol.receiveMessage();
        } catch(SocketError&) {
            break;
        }
    }
     */
    isRunning = false;
}

void ClientReceiver::stop() {
    keepRunning = false;
}

bool ClientReceiver::isDead() {
    return (! isRunning);
}

const std::string ClientReceiver::receiveUsername() {
    return protocol.receiveMessage();
}
