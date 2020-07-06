#include <iostream>
#include <string>
#include <vector>
#include <zconf.h>
#include "game_handler.h"
#include "exception.h"
#include "../../common/defines/username_confirmation.h"
#include "../sdl/exception.h"

GameHandler::GameHandler(const char *host, const char *port,
        const std::string& username, const uint8_t race_type,
        const uint8_t class_type) : socket(host, port, false),
        mapMonitor() {
    connectionSender = new ConnectionSender(socket, commandQueue);
    connectionSender->sendPlayerInfo(username, race_type, class_type);
    connectionReceiver = new ConnectionReceiver(socket, mapMonitor);
    checkUsername();
    printStartMessage();
    try {
        gameRender = new GameRender(960, 720, mapMonitor);
    } catch (SDLException& e) {
        std::cout << e.what();
    }
    inputHandler = new GameInputHandler(commandQueue, mapMonitor, gameRender);
}

GameHandler::~GameHandler() {
    delete connectionSender;
    delete connectionReceiver;
    delete gameRender;
    delete inputHandler;
}

void GameHandler::checkUsername() {
    int code = connectionReceiver->receiveUsernameConfirmation();
    if (code != USERNAME_OK) {
        delete connectionSender;
        delete connectionReceiver;
        switch (code) {
            case USERNAME_DUPLICATED:
                throw DuplicatedUsernameException();
            case NO_MORE_USERNAME_IDS:
                throw NoMoreAvailableIdsException();
            default:
                break;
        }
    }
}

void GameHandler::printStartMessage() {
    std::cout << "\n¡Jugador creado correctamente!\n" <<
              "El juego comenzará en unos instantes...\n";
}

void GameHandler::run() {
    connectionSender->start();
    connectionReceiver->start();
    gameRender->start();
    inputHandler->run();
}

void GameHandler::stop() {
    commandQueue.close();
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
    gameRender->stop();
    gameRender->join();
}
