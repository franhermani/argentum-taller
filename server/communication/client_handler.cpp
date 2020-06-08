#include <utility>
#include <iostream>
#include "client_handler.h"

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
    clientSender->start();
    clientReceiver->start();

    while (keepTalking) {
        // TODO: ver que va aca
    }
    isRunning = false;
}

void ClientHandler::stop() {
    clientSender->stop();
    clientSender->join();
    clientReceiver->stop();
    clientReceiver->join();
    keepTalking = false;
}

bool ClientHandler::isDead() {
    return (! isRunning);
}
