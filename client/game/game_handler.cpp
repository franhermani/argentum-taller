#include <iostream>
#include <vector>
#include <zconf.h>
#include "game_handler.h"

GameHandler::GameHandler(const char *host, const char *port,
        const char *username) : socket(host, port, false),
        mapMonitor() {
    connectionSender = new ConnectionSender(socket, commandQueue);
    connectionSender->sendUsername(username);
    inputHandler = new GameInputHandler(commandQueue);
    connectionReceiver = new ConnectionReceiver(socket, mapMonitor);
    gameRender = new GameRender(640*2, 480*2, mapMonitor);
    //TODO SACAR ESTO DE ACA
    gameRender->setTilesSize(10, 10);
}

GameHandler::~GameHandler() {
    delete connectionSender;
    delete connectionReceiver;
    delete gameRender;
    delete inputHandler;
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

