#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include "protocol.h"

#define BUF_MAX_SIZE 1024

ClientProtocol::ClientProtocol(Socket& socket) : socket(socket) {}

// TODO: tendria que recibir el ID del NPC u objeto o username de player
const char* ClientProtocol::encodeMessage(const std::string& message) {
    std::string type = message.substr(0,1);
    std::vector<char> v;

    if (type == "/") {
        // Comando
        // Copio los primeros 3 caracteres
        std::string command = message.substr(1,3);
        memcpy(&v[v.size()], command.c_str(), command.length());

        // Copio la longitud
        // TODO: modularizar esto
        /*
        uint16_t length;
        if (command == "med") {
            length = 0;
        } else if (command == "res") {
            bool id_sacerdote = false;
            length = id_sacerdote ? 3 : 0;
        } else if (command == "cur") {
            length = 3;
        } else if (command == "dep") {
            length = 8;
        } else if (command == "ret") {
            length = 8;
        } else if (command == "lis") {
            length = 3;
        } else if (command == "com") {
            length = 6;
        } else if (command == "ven") {
            length = 6;
        } else if (command == "tom") {
            length = 3;
        } else if (command == "tir") {
            length = 3;
        }
        */
        // Copio el contenido del mensaje
        // TODO: ...

    } else if (type == "@") {
        // Mensaje por el chat
        // encoded_msg = ...
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
