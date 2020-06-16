#include "connection_handler.h"

ConnectionHandler::ConnectionHandler(const char *host, const char *port) :
socket(host, port, false), gameRender(640*2, 480*2, 20,30){
    isRunning = true;



    //send related classes
    connectionSender = new ConnectionSender(socket, commandQueue);
    gameplay = new Gameplay(commandQueue);

    //receive related classes
    connectionReceiver = new ConnectionReceiver(socket, gameRender);
}

ConnectionHandler::~ConnectionHandler() {
    delete connectionSender;
    delete connectionReceiver;
    delete gameplay;
}



void ConnectionHandler::run() {

    // TODO: username leerlo por terminal, pasarselo a client y luego aca
    connectionSender->sendUsername("franhermani");
    /*connectionSender->start();
    connectionReceiver->start();
    gameplay->start();
     */
    isRunning = false;
}

void ConnectionHandler::stop() {
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
    gameplay->stop();
    gameplay->join();
}

bool ConnectionHandler::isDead() {
    return (! isRunning);
}
