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

std::vector<Terrain> ClientProtocol::receiveTerrains() {
    //devolvemos trucho
    std::vector<Terrain> received_terrain;
    for (int i = 0; i < 20 * 30; i++) {
        received_terrain.push_back(TERRAIN_LAND);
    }
    received_terrain[10] = TERRAIN_WATER;
    return std::move(received_terrain);
}

std::vector<npc_pos> ClientProtocol::receiveNpcs() {
    //VECTOR DE CHARACTERS QUE RECIBIRIAMOS POR SOCKET
    std::vector<npc_pos> npc_positions;
    npc_pos npc_1 = {0, 0, WARRIOR_RIGHT};
    npc_pos npc_2 = {3, 10, SKELETON_RIGHT};
    npc_positions.push_back(npc_1);
    npc_positions.push_back(npc_2);
    return std::move(npc_positions);
}
