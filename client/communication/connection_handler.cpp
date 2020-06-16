#include "connection_handler.h"

GameHandler::GameHandler(const char *host, const char *port, const char *username) :
socket(host, port, false), gameRender(640*2, 480*2, 20,30){
    isRunning = true;

    connectionSender = new ConnectionSender(socket, commandQueue);
    connectionSender->sendUsername(username);
    gameplay = new Gameplay(commandQueue);
    connectionReceiver = new ConnectionReceiver(socket, gameRender);

}

GameHandler::~GameHandler() {
    delete connectionSender;
    delete connectionReceiver;
    delete gameplay;
}



void GameHandler::run() {

    // TODO: username leerlo por terminal, pasarselo a client y luego aca
    connectionSender->start();
    connectionReceiver->start();
    gameplay->start();

    isRunning = false;
}

void GameHandler::stop() {
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
    gameplay->stop();
    gameplay->join();
}

bool GameHandler::isDead() {
    return (! isRunning);
}
