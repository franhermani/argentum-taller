#include <string>
#include <vector>
#include <cstring>
#include "protocol.h"
#include "../../common/defines/debug.h"
#include "../../common/defines/world_structs.h"
#define SIZE_32 4
#define SIZE_16 2
#define SIZE_8 1
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

matrix_t ClientProtocol::receiveMatrix() {

    std::vector<char> matrix_data_buffer(STATIC_TERRAIN_PART_SIZE, 0);
    socket.receiveBytes(matrix_data_buffer.data(), STATIC_TERRAIN_PART_SIZE);
    matrix_t m;
    int bytes_advanced = 0;

    uint16_t length;
    memcpy(&length, matrix_data_buffer.data(), SIZE_16);
    m.length = ntohs(length);
    bytes_advanced += SIZE_16;

    uint16_t width;
    memcpy(&width, matrix_data_buffer.data()+bytes_advanced, SIZE_16);
    m.width = ntohs(width);
    bytes_advanced += SIZE_16;

    uint16_t height;
    memcpy(&height, matrix_data_buffer.data()+bytes_advanced, SIZE_16);
    m.height = ntohs(height);




    int matrix_length = m.length-HEIGHT_PLUS_WIDTH_SIZE;
    std::vector<char> matrix_buffer(matrix_length,0);
    socket.receiveBytes(matrix_buffer.data(), matrix_length);

    std::vector<Terrain> terrains;
    terrains.resize(m.height*m.width);
    int current_index = 0;
    for (int i=0; i<m.height*m.width; i++) {
        uint8_t terrain_type = (uint8_t) matrix_buffer[current_index];
        terrains[i] = static_cast<Terrain>(terrain_type);
        ++current_index;
    }
    m.terrains = terrains;
    return std::move(m);

}

world_t ClientProtocol::receiveWorld() {

    world_t w;
    std::vector<char> length_buffer(SIZE_16, 0);
    socket.receiveBytes(length_buffer.data(), SIZE_16);
    uint16_t length;
    memcpy(&length, length_buffer.data(), SIZE_16);
    w.length = ntohs(length);
    std::cout << "\n\n numero de l " << w.length << "\n\n";


    int bytes_advanced = 0;

    std::vector<char> world_buffer(w.length,0);
    socket.receiveBytes(world_buffer.data(), w.length);


    // recibimos player principal
    player_info_t player_info;
    w.player_info = player_info;

    uint16_t actual_life;
    memcpy(&actual_life, world_buffer.data()+bytes_advanced, SIZE_16);
    w.player_info.actual_life = ntohs(actual_life);
    bytes_advanced += SIZE_16;

    uint16_t max_life;
    memcpy(&max_life, world_buffer.data()+bytes_advanced, SIZE_16);
    w.player_info.max_life = ntohs(max_life);
    bytes_advanced += SIZE_16;


    uint16_t actual_mana;
    memcpy(&actual_mana, world_buffer.data()+bytes_advanced, SIZE_16);
    w.player_info.actual_mana = ntohs(actual_mana);
    bytes_advanced += SIZE_16;


    uint16_t max_mana;
    memcpy(&max_mana, world_buffer.data()+bytes_advanced, SIZE_16);
    w.player_info.max_mana = ntohs(max_mana);
    bytes_advanced += SIZE_16;


    uint16_t actual_gold;
    memcpy(&actual_gold, world_buffer.data()+bytes_advanced, SIZE_16);
    w.player_info.actual_gold = ntohs(actual_gold);
    bytes_advanced += SIZE_16;


    uint16_t max_gold;
    memcpy(&max_gold, world_buffer.data()+bytes_advanced, SIZE_16);
    w.player_info.max_gold = ntohs(max_gold);
    bytes_advanced += SIZE_16;


    uint16_t level;
    memcpy(&level, world_buffer.data()+bytes_advanced, SIZE_16);
    w.player_info.level = ntohs(level);
    bytes_advanced += SIZE_16;


    uint32_t experience;
    memcpy(&experience, world_buffer.data()+bytes_advanced, SIZE_32);
    w.player_info.actual_experience = ntohl(experience);
    bytes_advanced += SIZE_32;



    std::cout << "\n\nrecibi esto: actual life: " << w.player_info.actual_life << " max life " << w.player_info.max_life
              << " actual mana " << w.player_info.actual_mana << " max mana " << w.player_info.max_mana
              << " actual gold " << w.player_info.actual_gold << " max gold " << w.player_info.max_gold
              << " actual_experience " << w.player_info.actual_experience << " level " << w.player_info.level << "\n\n";

    //recibimos inventario
    inventory_t inventory;
    //simulo que avance el inventario
    bytes_advanced += (SIZE_8 * 9 + SIZE_16);

    uint16_t num_players;
    memcpy(&num_players, world_buffer.data()+bytes_advanced, SIZE_16);
    w.num_players = ntohs(num_players);
    bytes_advanced += SIZE_16;
    std::cout << "\n\n numero de players " << w.num_players << "\n\n";
    std::vector<player_t> players;
    players.resize(w.num_players);
    for (int i = 0; i < w.num_players; i ++) {
        player_t player;

        uint16_t id;                // Id
        memcpy(&id, world_buffer.data()+bytes_advanced, SIZE_16);
        player.id = ntohs(id);
        bytes_advanced += SIZE_16;

        uint16_t pos_x;             // Pos x en la matriz
        memcpy(&pos_x, world_buffer.data()+bytes_advanced, SIZE_16);
        player.pos_x = ntohs(pos_x);
        bytes_advanced += SIZE_16;


        uint16_t pos_y;             // Pos y en la matriz
        memcpy(&pos_y, world_buffer.data()+bytes_advanced, SIZE_16);
        player.pos_y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        uint8_t is_alive;           // 1 si esta vivo, 0 si no (fantasma)
        memcpy(&is_alive, world_buffer.data()+bytes_advanced, SIZE_8);
        player.is_alive = is_alive;
        bytes_advanced += SIZE_8;

        uint8_t orientation;        // Enum type de la orientacion
        memcpy(&orientation, world_buffer.data()+bytes_advanced, SIZE_8);
        player.orientation = orientation;
        bytes_advanced += SIZE_8;

        uint8_t race_type;          // Enum type de la raza
        memcpy(&race_type, world_buffer.data()+bytes_advanced, SIZE_8);
        player.race_type = race_type;
        bytes_advanced += SIZE_8;


        uint8_t class_type;         // Enum type de la clase
        memcpy(&class_type, world_buffer.data()+bytes_advanced, SIZE_8);
        player.class_type = class_type;
        bytes_advanced += SIZE_8;


        uint8_t body_armor;         // Enum type de la armadura o vestimenta
        memcpy(&body_armor, world_buffer.data()+bytes_advanced, SIZE_8);
        player.body_armor = body_armor;
        bytes_advanced += SIZE_8;

        uint8_t head_armor;         // Enum type del casco o sombrero
        memcpy(&head_armor, world_buffer.data()+bytes_advanced, SIZE_8);
        player.head_armor = head_armor;
        bytes_advanced += SIZE_8;

        uint8_t weapon;             // Enum type del arma
        memcpy(&weapon, world_buffer.data()+bytes_advanced, SIZE_8);
        player.weapon = weapon;
        bytes_advanced += SIZE_8;

        players[i] = player;

        std::cout << "\n\nrecibi este player: id: " << player.id << " posx: " << player.pos_x << " posy: " << player.pos_y
         << " is alive " << (int) player.is_alive << " orientation: "<< (int)player.orientation << " race type " <<  (int)player.race_type
         << " class type " <<(int) player.class_type << " body armor " << player.body_armor << " head armor " << player.head_armor
         << " weapong " << player.weapon << "\n\n";


    }
    w.players = players;
    return std::move(w);
}
