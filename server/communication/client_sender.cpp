#include <string>
#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket) : protocol(socket) {
    keepRunning = true;
    isRunning = true;
}

void ClientSender::run() {
    std::string message;

    while (keepRunning) {
        try {
            message = "Chau mundo";
            protocol.sendMessage(message);
        } catch(SocketError&) {
            break;
        }
    }
    isRunning = false;
}

void ClientSender::stop() {
    keepRunning = false;
}

bool ClientSender::isDead() {
    return (! isRunning);
}
