#include <vector>
#include <utility>
#include <chrono>
#include "client_handler.h"
#include "utilities/blocking_vector.h"
#include "game/id_manager.h"
#include "../common/defines/username_confirmation.h"

#define COMMUNICATION_WAIT_TIME 1000

ClientHandler::ClientHandler(Socket socket_received,
        GameManager& game_manager, BlockingVector& clients) :
        socket(std::move(socket_received)), gameManager(game_manager),
        clients(clients) {
    isRunning = true;
    clientReceiver = new ClientReceiver(socket, gameManager.commandQueue);
    clientSender = new ClientSender(socket, gameManager.worldMonitor,
            gameManager.msPerSend);

    checkUsername();
}

ClientHandler::~ClientHandler() {
    delete clientSender;
    delete clientReceiver;
    gameManager.removePlayerFromWorld(player->id);
    delete player;
}

void ClientHandler::checkUsername() {
    std::vector<char> info = clientReceiver->receivePlayerInfo();
    int race_type = info[0], class_type = info[1];
    std::string username(info.begin() + 2, info.end());

    try {
        int id = gameManager.addIdByUsername(username);
        clientSender->sendUsernameConfirmation(USERNAME_OK);
        player = new Player(gameManager.world, gameManager.equations,
                            id, race_type, class_type);
    } catch (DuplicatedUsernameException&) {
        clientSender->sendUsernameConfirmation(USERNAME_DUPLICATED);
        delete clientSender;
        delete clientReceiver;
        throw DuplicatedUsernameException();
    } catch (NoMoreAvailableIdsException&) {
        clientSender->sendUsernameConfirmation(NO_MORE_USERNAME_IDS);
        delete clientSender;
        delete clientReceiver;
        throw NoMoreAvailableIdsException();
    }
}

void ClientHandler::run() {
    using ms = std::chrono::milliseconds;

    gameManager.addPlayerToWorld(player);
    clientReceiver->setPlayer(player);
    clientSender->setPlayer(player);
    clientReceiver->start();
    clientSender->start();

    while (true) {
        std::this_thread::sleep_for(ms(COMMUNICATION_WAIT_TIME));
        if (clientReceiver->isDead() || clientSender->isDead()) {
            isRunning = false;
            break;
        }
    }
    clients.notifyClientsCleaner();
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
