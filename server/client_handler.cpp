#include <vector>
#include <utility>
#include <chrono>
#include "client_handler.h"
#include "game/id_manager.h"

#define COMMUNICATION_WAIT_TIME 1000

ClientHandler::ClientHandler(Socket socket_received,
        GameManager& game_manager) : socket(std::move(socket_received)),
        gameManager(game_manager) {
    isRunning = true;
    clientReceiver = new ClientReceiver(socket,*gameManager.commandQueue);
    clientSender = new ClientSender(socket, *gameManager.worldMonitor,
            gameManager.msPerSend);
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;
    gameManager.removePlayerFromWorld(player->id);
    delete player;
}

void ClientHandler::run() {
    using ms = std::chrono::milliseconds;

    std::vector<char> info = clientReceiver->receivePlayerInfo();
    int race_type = info[0], class_type = info[1];
    std::string username(info.begin() + 2, info.end());

    try {
        int id = gameManager.addIdByUsername(username);
        player = new Player(*gameManager.world, *gameManager.equations,
                            id, race_type, class_type);

        gameManager.addPlayerToWorld(player);
        clientReceiver->setPlayer(player);
        clientSender->setPlayer(player);
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
    } catch (DuplicatedUsernameException&) {
        // TODO: enviar mensaje al cliente
    } catch (NoMoreAvailableIdsException&) {
        // TODO: enviar mensaje al cliente
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
