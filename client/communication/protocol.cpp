#include <string>
#include <vector>
#include <cstring>
#include "protocol.h"
#include "../../common/defines/debug.h"
#include "../../common/defines/world_structs.h"
#define TWO_BYTES_SIZE 2
#define STATIC_PART_SIZE 6
#define HEIGHT_PLUS_WIDTH_SIZE 4

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

void ClientProtocol::initializeMap(GameRender& gameRender) {
    //devolvemos trucho
    /*
    for (int i = 0; i < 20 * 30; i++) {
        received_terrain.push_back(TERRAIN_LAND);
    }
    received_terrain[10] = TERRAIN_WATER;*/
    //TODO sacar nros magicos

    std::vector<char> matrix_data_buffer(STATIC_PART_SIZE,0);
    socket.receiveBytes(matrix_data_buffer.data(), STATIC_PART_SIZE);
    matrix_t m;
    int bytes_advanced = 0;

    uint16_t length;
    memcpy(&length, matrix_data_buffer.data(), TWO_BYTES_SIZE);
    m.length = ntohs(length);
    bytes_advanced += TWO_BYTES_SIZE;

    uint16_t width;
    memcpy(&width, matrix_data_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    m.width = ntohs(width);
    bytes_advanced += TWO_BYTES_SIZE;

    uint16_t height;
    memcpy(&height, matrix_data_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    m.height = ntohs(height);

    gameRender.setTilesSize(m.width, m.height);


    int matrix_length = m.length-HEIGHT_PLUS_WIDTH_SIZE;
    /*

    std::vector<char> matrix_buffer(matrix_length,0);
    socket.receiveBytes(matrix_buffer.data(), matrix_length);
    std::vector<Terrain> received_terrain;
    for (int i=0; i<matrix_length; i++) {
        uint8_t terrain_type = (uint8_t) matrix_buffer[i];
        received_terrain.push_back(static_cast<Terrain>(terrain_type));
    }
     */

    std::vector<char> matrix_buffer(matrix_length,0);
    socket.receiveBytes(matrix_buffer.data(), matrix_length);
    std::vector<std::vector<Terrain>> received_terrain;


    received_terrain.resize(m.height);
    int current_index = 0;
    for (int i=0; i<m.height; i++) {
        std::vector<Terrain> row;
        row.resize(m.width);
        received_terrain.push_back(row);
        for (int j = 0; j < m.width; ++j) {
            uint8_t terrain_type = (uint8_t) matrix_buffer[current_index];
            received_terrain[i].push_back(static_cast<Terrain>(terrain_type));
            ++current_index;
        }
    }
    gameRender.renderTerrain(received_terrain);

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
