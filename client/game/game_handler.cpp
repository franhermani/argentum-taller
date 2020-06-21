#include <iostream>
#include <vector>
#include <zconf.h>
#include "game_handler.h"

GameHandler::GameHandler(const char *host, const char *port,
        const char *username) : socket(host, port, false),
        gameRender(640*2, 480*2) {
    connectionSender = new ConnectionSender(socket, commandQueue);
    connectionSender->sendUsername(username);
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

