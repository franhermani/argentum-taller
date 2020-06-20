#include <string>
#include <vector>
#include <cstring>
#include "protocol.h"
#include "../../common/defines/debug.h"
#include "../../common/defines/world_structs.h"
#define TWO_BYTES_SIZE 2
#define STATIC_TERRAIN_PART_SIZE 6
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

    std::vector<char> matrix_data_buffer(STATIC_TERRAIN_PART_SIZE, 0);
    socket.receiveBytes(matrix_data_buffer.data(), STATIC_TERRAIN_PART_SIZE);
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

    //TODO sacar a otra funcion. esta se hizo larga. una que haga la matriz
    int matrix_length = m.length-HEIGHT_PLUS_WIDTH_SIZE;
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

void ClientProtocol::receiveWorld(GameRender& gameRender) {

    world_t w;
    std::vector<char> length_buffer(TWO_BYTES_SIZE, 0);
    socket.receiveBytes(length_buffer.data(), TWO_BYTES_SIZE);
    uint16_t length;
    memcpy(&length, length_buffer.data(), TWO_BYTES_SIZE);
    w.length = ntohs(length);

    int bytes_advanced = 0;

    std::vector<char> world_buffer(w.length,0);
    socket.receiveBytes(world_buffer.data(), w.length);

    player_info_t player_info;
    w.player_info = player_info;

    uint16_t actual_life;
    memcpy(&actual_life, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    player_info.actual_life = ntohs(actual_life);
    bytes_advanced += TWO_BYTES_SIZE;

    uint16_t max_life;
    memcpy(&max_life, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    player_info.max_life = ntohs(max_life);
    bytes_advanced += TWO_BYTES_SIZE;


    uint16_t actual_mana;
    memcpy(&actual_mana, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    player_info.actual_mana = ntohs(actual_mana);
    bytes_advanced += TWO_BYTES_SIZE;


    uint16_t max_mana;
    memcpy(&max_mana, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    w.player_info.max_mana = ntohs(max_mana);
    bytes_advanced += TWO_BYTES_SIZE;


    uint16_t actual_gold;
    memcpy(&actual_gold, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    w.player_info.actual_gold = ntohs(actual_gold);
    bytes_advanced += TWO_BYTES_SIZE;


    uint16_t max_gold;
    memcpy(&max_gold, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    w.player_info.max_gold = ntohs(max_gold);
    bytes_advanced += TWO_BYTES_SIZE;


    uint16_t experience;
    memcpy(&experience, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    w.player_info.experience = ntohs(experience);
    bytes_advanced += TWO_BYTES_SIZE;


    uint16_t level;
    memcpy(&level, world_buffer.data()+bytes_advanced, TWO_BYTES_SIZE);
    w.player_info.level = ntohs(level);
    bytes_advanced += TWO_BYTES_SIZE;

    std::cout << "recibi esto: actual life: "<< w.player_info.actual_life << " max life "<<w.player_info.max_life
    << " actual mana " << w.player_info.actual_mana << " max mana " << w.player_info.max_mana
    << " actual gold " << w.player_info.actual_gold << " max gold " << w.player_info.max_gold
    << " experience " << w.player_info.experience << " level " << w.player_info.level << "\n";

    inventory_t inventory;

    


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
