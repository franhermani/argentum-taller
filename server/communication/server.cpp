#include <iostream>
#include <exception>
#include "server.h"

Server::Server(File& file) : fileParser(file), gameManager(fileParser) {
    port = fileParser.getPort();
    if (port.empty()) throw std::runtime_error("No se especificó el puerto\n");
    threadAcceptor = new ThreadAcceptor(0, port.c_str());
}

Server::~Server() {
    delete threadAcceptor;
}

void Server::startThreadAcceptor() {
    threadAcceptor->start();
}

void Server::stopThreadAcceptor() {
    threadAcceptor->stop();
}

void Server::joinThreadAcceptor() {
    threadAcceptor->join();
}
