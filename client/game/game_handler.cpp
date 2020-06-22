#include <iostream>
#include <vector>
#include <zconf.h>
#include "game_handler.h"

GameHandler::GameHandler(const char *host, const char *port,
        const std::string& username, const uint8_t race_type,
        const uint8_t class_type) : socket(host, port, false),
        gameRender(640*2, 480*2) {
    connectionSender = new ConnectionSender(socket, commandQueue);
    connectionSender->sendPlayerInfo(username, race_type, class_type);
    inputHandler = new GameInputHandler(commandQueue);
    connectionReceiver = new ConnectionReceiver(socket, gameRender);
}

GameHandler::~GameHandler() {
    delete connectionSender;
    delete connectionReceiver;
    delete inputHandler;
}

void GameHandler::run() {
    connectionSender->start();
    connectionReceiver->start();
    inputHandler->run();
}

void GameHandler::stop() {
    commandQueue.close();
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
}

