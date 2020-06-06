#include <string>
#include <fstream>
#include "server.h"
#include "file.h"

Server::Server(File& file) : configFile(file) {}

Server::~Server() {
    delete threadAcceptor;
}

void Server::parseConfigFile() {
    // TODO: tener el archivo en formato json y usar jsoncpp
    std::string line;
    while (getline(configFile.getFile(), line)) {
        // ...
    }
    configFile.closeFD();
}

void Server::createThreadAcceptor() {
    const char *host = 0;
    // TODO: esto se lee del archivo
    port = "8080";
    threadAcceptor = new ThreadAcceptor(host, port);
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
