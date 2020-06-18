#include <utility>
#include <iostream>
#include "client_handler.h"

ClientHandler::ClientHandler(Socket socket_received,
        GameManager& game_manager) : socket(std::move(socket_received)),
        gameManager(game_manager) {
    isRunning = true;
    clientReceiver = new ClientReceiver(socket,
            *gameManager.getCommandQueue());
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;
    gameManager.removePlayerFromWorld(player->id);
    delete player;
}

void ClientHandler::run() {
    // Recibo el username
    std::string username = clientReceiver->receiveUsername();

    // Agrego el ID del player al manager
    int id = gameManager.addIdByUsername(username);

    // Creo el player
    player = new Player(*gameManager.getWorld(), id);

    // Agrego el player al world
    gameManager.addPlayerToWorld(player);

    clientSender = new ClientSender(socket, *gameManager.getWorldMonitor(),
            *player);

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
