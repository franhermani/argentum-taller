#include <string>
#include <vector>
#include <cstring>
#include "protocol.h"
#include "../../common/defines/debug.h"

ClientProtocol::ClientProtocol(Socket& socket) : socket(socket) {}

void ClientProtocol::sendCommand(CommandDTO& command) {
    std::vector<char> byte_msg = command.serialize();
    socket.sendBytes(byte_msg.data(), byte_msg.size());

    if (debug) {
        std::cout << "Comando enviado: ";
        for (char& i : byte_msg)
            printf("%02X ", (unsigned) (unsigned char) i);
        std::cout << "\n";
    }
}

void ClientProtocol::sendUsername(const std::string& username) {
    // Longitud total
    size_t total_size = sizeof(uint8_t) + username.length();

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Longitud del username
    byte_msg[0] = username.length();

    // Username
    memcpy(&byte_msg[1], username.c_str(), username.length());

    socket.sendBytes(byte_msg.data(), byte_msg.size());
}
