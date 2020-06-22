#include <vector>
#include <utility>
#include <chrono>
#include "client_handler.h"

#define COMMUNICATION_WAIT_TIME 1000

ClientHandler::ClientHandler(Socket socket_received,
        GameManager& game_manager) : socket(std::move(socket_received)),
        gameManager(game_manager) {
    isRunning = true;
    clientReceiver = new ClientReceiver(socket,*gameManager.commandQueue);
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;
    gameManager.removePlayerFromWorld(player->id);
    delete player;
}

void ClientHandler::run() {
    using ms = std::chrono::milliseconds;

    // Recibo la info del player
    std::vector<char> info = clientReceiver->receivePlayerInfo();
    int race_type = info[0], class_type = info[1];
    std::string username(info.begin() + 2, info.end());

    // Agrego el ID del player al manager
    int id = gameManager.addIdByUsername(username);

    // Creo el player
    player = new Player(*gameManager.world, *gameManager.equations,
            id, race_type, class_type);

    // Agrego el player al world
    gameManager.addPlayerToWorld(player);

    // Le paso el player al receiver ya que lo necesita para los commands
    clientReceiver->setPlayer(player);

    clientSender = new ClientSender(socket, *gameManager.worldMonitor,
            *player, gameManager.msPerSend);

    clientReceiver->start();
    clientSender->start();

    while (true) {
        // TODO: preguntar si esta bien este sleep
        std::this_thread::sleep_for(ms(COMMUNICATION_WAIT_TIME));
        if (clientReceiver->isDead() || clientSender->isDead()) {
            isRunning = false;
            break;
        }
    }
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
