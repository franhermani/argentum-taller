#include "connection_handler.h"

GameHandler::GameHandler(const char *host, const char *port, const char *username) :
socket(host, port, false), gameRender(640*2, 480*2, 20,30){
    isRunning = true;

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

    // TODO: username leerlo por terminal, pasarselo a client y luego aca
    connectionSender->start();
    connectionReceiver->start();
    inputHandler->start();

    isRunning = false;
}

void GameHandler::stop() {
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
    inputHandler->stop();
    inputHandler->join();
}

bool GameHandler::isDead() {
    return (! isRunning);
}
