#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include "server.h"
#include "defines.h"
#include "file.h"
#include "json/json.hpp"

Server::Server(File& file) {
    parseConfigFile(file);
    if (port.empty()) throw std::runtime_error("No se especificó el puerto\n");
    threadAcceptor = new ThreadAcceptor(0, port.c_str());
}

Server::~Server() {
    delete threadAcceptor;
}

void Server::parseConfigFile(File& file) {
    using json = nlohmann::json;
    json j;

    // Convierto el archivo a una estructura json
    file.getFile() >> j;

    // Obtengo el puerto
    port = j[PORT].get<std::string>();

    file.closeFD();
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
