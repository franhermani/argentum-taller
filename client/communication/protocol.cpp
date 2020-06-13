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
    std::vector<char> v;

    // Copio la abreviatura (primeros 4 caracteres)
//    std::string abbr = message.substr(0,3);
//    memcpy(&v[v.size()], abbr.c_str(), abbr.length());

    // Copio la longitud
    // TODO: modularizar esto
    /*
    uint16_t length;
    if (abbr == "user") {
        length = length(username);
    } else if (abbr == "medi") {
        length = 0;
    } else if (abbr == "resu") {
        bool id_sacerdote = false;
        length = id_sacerdote ? 4 : 0;
    } else if (abbr == "cura") {
        length = 4;
    } else if (abbr == "depo") {
        length = 10;
    } else if (abbr == "reti") {
        length = 10;
    } else if (abbr == "list") {
        length = 4;
    } else if (abbr == "comp") {
        length = 8;
    } else if (abbr == "vend") {
        length = 8;
    } else if (abbr == "toma") {
        length = 4;
    } else if (abbr == "tira") {
        length = 4;
    }
    */
    // Copio el contenido del mensaje
    // TODO: ...

    return v.data();
}

const std::string ClientProtocol::decodeMessage(const char* message) {
    // TODO: ...
    return "Hola mundo";
}

void ClientProtocol::sendMessage(const std::string& message) {
    // TODO: ...
//    encodeMessage(message);
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
