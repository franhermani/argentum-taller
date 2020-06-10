#include <utility>
#include <iostream>
#include "client_handler.h"

ClientHandler::ClientHandler(Socket socket_received) :
socket(std::move(socket_received)) {
    keepRunning = true;
    isRunning = true;
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

    while (keepRunning) {
        // TODO: ver que va aca
    }
    isRunning = false;
}

void ClientHandler::stop() {
    clientSender->stop();
    clientSender->join();
    clientReceiver->stop();
    clientReceiver->join();
    keepRunning = false;
}

bool ClientHandler::isDead() {
    return (! isRunning);
}
