#include <utility>
#include <iostream>
#include "client_handler.h"

ClientHandler::ClientHandler(Socket socket_received,
        GameManager& game_manager) : socket(std::move(socket_received)),
        gameManager(game_manager) {
    isRunning = true;
    clientReceiver = new ClientReceiver(socket, *gameManager.getWorld());
    clientSender = new ClientSender(socket, *gameManager.getWorld());
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;
    gameManager.removePlayerFromWorld(player->id);
    delete player;
}

void ClientHandler::run() {
    std::string username = clientReceiver->receiveUsername();
    int id = gameManager.addIdByUsername(username);
    player = new Player(*gameManager.getWorld(), id);
    gameManager.addPlayerToWorld(player);

    clientReceiver->addPlayer(player);
    clientSender->addPlayer(player);

    clientReceiver->start();
    clientSender->start();

    isRunning = false;
}

void ClientHandler::stop() {
    clientReceiver->stop();
    clientSender->stop();
    clientReceiver->join();
    clientSender->join();
}

bool ClientHandler::isDead() {
    return (! isRunning);
}
