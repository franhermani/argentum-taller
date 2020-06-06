#include <string>
#include <fstream>
#include "server.h"
#include "defines.h"
#include "file.h"
#include "json/json.hpp"

Server::Server(File& file) : configFile(file) {}

Server::~Server() {
    delete threadAcceptor;
}

void Server::parseConfigFile() {
    using json = nlohmann::json;
    json j;

    // Convierto el archivo a una estructura json
    configFile.getFile() >> j;

    // Obtengo el puerto
    std::string port_str = j[PORT].get<std::string>();
    port = port_str.c_str();

    configFile.closeFD();
}

void Server::createThreadAcceptor() {
    const char *host = 0;
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
