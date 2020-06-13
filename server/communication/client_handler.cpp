#include <utility>
#include <iostream>
#include "client_handler.h"

ClientHandler::ClientHandler(Socket socket_received,
        GameManager& game_manager) : socket(std::move(socket_received)),
        gameManager(game_manager) {
    isRunning = true;
    clientSender = new ClientSender(socket);
    clientReceiver = new ClientReceiver(socket);
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;
}

void ClientHandler::run() {
    username = clientReceiver->receiveUsername();
    gameManager.addPlayer(username);
    clientSender->start();
    clientReceiver->start();
    isRunning = false;
}

void ClientHandler::stop() {
    clientSender->stop();
    clientSender->join();
    clientReceiver->stop();
    clientReceiver->join();
}

bool ClientHandler::isDead() {
    return (! isRunning);
}
