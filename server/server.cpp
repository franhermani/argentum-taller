#include <iostream>
#include <exception>
#include "server.h"

Server::Server(File& file) {
    port = jsonParser.getPort(file);
    if (port.empty()) throw std::runtime_error("No se especificó el puerto\n");
    gameManager = new GameManager(file);
    clientsAcceptor = new ClientsAcceptor(0, port.c_str(), *gameManager);
}

Server::~Server() {
    delete gameManager;
    delete clientsAcceptor;
}

void Server::startGame() {
    gameManager->start();
    clientsAcceptor->start();
}

void Server::endGame() {
    clientsAcceptor->stop();
    clientsAcceptor->join();
}
