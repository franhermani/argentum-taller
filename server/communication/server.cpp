#include <iostream>
#include <exception>
#include "server.h"

Server::Server(File& file) : fileParser(file), gameManager(fileParser) {
    port = fileParser.getPort();
    if (port.empty()) throw std::runtime_error("No se especificó el puerto\n");
    clientsAcceptor = new ClientsAcceptor(0, port.c_str());
}

Server::~Server() {
    delete clientsAcceptor;
}

void Server::startClientsAcceptor() {
    clientsAcceptor->start();
}

void Server::stopClientsAcceptor() {
    clientsAcceptor->stop();
}

void Server::joinClientsAcceptor() {
    clientsAcceptor->join();
}
