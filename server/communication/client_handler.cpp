#include <utility>
#include <iostream>
#include "client_handler.h"

ClientHandler::ClientHandler(Socket socket_received,
        GameManager& game_manager) : socket(std::move(socket_received)),
        gameManager(game_manager) {
    isRunning = true;
    clientSender = new ClientSender(socket, *gameManager.getWorld());
    clientReceiver = new ClientReceiver(socket, *gameManager.getWorld());
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;

    gameManager.getWorld()->removePlayer(player->id);
    delete player;
}

void ClientHandler::run() {
    std::string username = clientReceiver->receiveUsername();
    int id = gameManager.addIdByUsername(username);
    player = new Player(*gameManager.getWorld(), id);

    clientSender->addPlayer(player);
    clientReceiver->addPlayer(player);

    clientSender->start();
    clientReceiver->start();

    isRunning = false;
}

void ClientHandler::stop() {
    clientSender->stop();
    clientReceiver->stop();
    clientSender->join();
    clientReceiver->join();
}

bool ClientHandler::isDead() {
    return (! isRunning);
}
