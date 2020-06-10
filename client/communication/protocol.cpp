#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include "protocol.h"

#define BUF_MAX_SIZE 1024

ClientProtocol::ClientProtocol(Socket& socket) : socket(socket) {}

// TODO: tendria que recibir el ID del NPC, Player u Objeto
const char* ClientProtocol::encodeMessage(const std::string& message) {
    std::string type = message.substr(0,1);
    std::vector<char> v;

    // Comando
    if (type == "/") {
        // Copio los primeros 4 caracteres
        std::string command = message.substr(1,4);
        memcpy(&v[v.size()], command.c_str(), command.length());

        // Copio la longitud
        // TODO: modularizar esto
        /*
        uint16_t length;
        if (command == "medi") {
            length = 0;
        } else if (command == "resu") {
            bool id_sacerdote = false;
            length = id_sacerdote ? 4 : 0;
        } else if (command == "cura") {
            length = 4;
        } else if (command == "depo") {
            length = 10;
        } else if (command == "reti") {
            length = 10;
        } else if (command == "list") {
            length = 4;
        } else if (command == "comp") {
            length = 8;
        } else if (command == "vend") {
            length = 8;
        } else if (command == "toma") {
            length = 4;
        } else if (command == "tira") {
            length = 4;
        }
        */
        // Copio el contenido del mensaje
        // TODO: ...
    }
    return v.data();
}

const std::string ClientProtocol::decodeMessage(const char* message) {
    // TODO: ...
    return "Hola mundo";
}

void ClientProtocol::sendMessage(const std::string& message) {
    // TODO: ...
    encodeMessage(message);
    socket.sendBytes(message.c_str(), message.length());
}

const std::string ClientProtocol::receiveMessage() {
    // TODO: ...
    char buffer[BUF_MAX_SIZE];
    socket.receiveBytes(buffer, 10);
    buffer[10] = '\0';
    std::string str(buffer);
    std::cout << buffer << "\n";
    // TODO: decodeMessage(str);
    return buffer;
}
