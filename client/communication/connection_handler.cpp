#include "connection_handler.h"

ConnectionHandler::ConnectionHandler(const char *host, const char *port) :
socket(host, port, false) {
    isRunning = true;



    //send related classes
    connectionSender = new ConnectionSender(socket);
    gameplay = new Gameplay();


    //receive related classes
    connectionReceiver = new ConnectionReceiver(socket);
    GameRender gameRender(640*2, 480*2, 20,30);
}

ConnectionHandler::~ConnectionHandler() {
    delete connectionSender;
    delete connectionReceiver;
}



void ConnectionHandler::run() {

    // TODO: username leerlo por terminal, pasarselo a client y luego aca
    connectionSender->sendUsername("franhermani");
    /*connectionSender->start();
    connectionReceiver->start();*/
    isRunning = false;
}

void ConnectionHandler::stop() {
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
}

bool ConnectionHandler::isDead() {
    return (! isRunning);
}
