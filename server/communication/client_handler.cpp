#include <utility>
#include <iostream>
#include "client_handler.h"
#include "../../common/socket_error.h"

ClientHandler::ClientHandler(Socket socket) : socket(std::move(socket)),
keepTalking(true), isRunning(true), isFinished(false) {
    clientSender = new ClientSender(socket);
    clientReceiver = new ClientReceiver(socket);
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;
}

void ClientHandler::run() {
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

void ClientHandler::stop() {
    keepTalking = false;
}

const bool ClientHandler::isDead() {
    return (! isRunning);
}
