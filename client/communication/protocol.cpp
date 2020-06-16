#include <iostream>
#include <vector>
#include "protocol.h"

ClientProtocol::ClientProtocol(Socket& socket) : socket(socket) {}

void ClientProtocol::sendCommand(Command& command) {
    std::vector<char> byte_msg = command.serialize();
    socket.sendBytes(byte_msg.data(), byte_msg.size());

    // DEBUG
//    for (char i : byte_msg) printf("%02X ", (unsigned) (unsigned char) i);
//    printf("\n");
}
