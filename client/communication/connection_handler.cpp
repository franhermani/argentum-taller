#include <utility>
#include <iostream>
#include "connection_handler.h"

ConnectionHandler::ConnectionHandler(const char *host, const char *port) :
socket(host, port, false), keepTalking(true), isRunning(true),
isFinished(false) {
    connectionSender = new ConnectionSender(socket);
    connectionReceiver = new ConnectionReceiver(socket);
}

ConnectionHandler::~ConnectionHandler() {
    delete connectionSender;
    delete connectionReceiver;
}

void ConnectionHandler::run() {
    connectionSender->start();
    connectionReceiver->start();

    while (keepTalking) {
        // TODO: ver que va aca
    }
    isRunning = false;
}

void ConnectionHandler::stop() {
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
    keepTalking = false;
}

bool ConnectionHandler::isDead() {
    return (! isRunning);
}
