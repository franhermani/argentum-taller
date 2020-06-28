#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include "protocol.h"
#include "../../common/defines/debug.h"

#define SIZE_8                      sizeof(uint8_t)
#define SIZE_16                     sizeof(uint16_t)
#define SIZE_32                     sizeof(uint32_t)
#define STATIC_TERRAIN_PART_SIZE    6
#define HEIGHT_PLUS_WIDTH_SIZE      4

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

void ClientProtocol::sendPlayerInfo(const std::string& username,
        const uint8_t race_type, const uint8_t class_type) {
    // Longitud total
    size_t total_size = 3*SIZE_8 + username.length();

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Longitud del username
    byte_msg[0] = 2*SIZE_8 + username.length();

    // Raza
    byte_msg[1] = race_type;

    // Clase
    byte_msg[2] = class_type;

    // Username
    memcpy(&byte_msg[3], username.c_str(), username.length());

    socket.sendBytes(byte_msg.data(), byte_msg.size());
}


const int ClientProtocol::receiveUsernameConfirmation() {
    std::vector<char> code;
    code.resize(SIZE_8);
    socket.receiveBytes(code.data(), SIZE_8);
    return (int) code[0];
}

const int ClientProtocol::receiveUsernameId() {
    std::vector<char> byte_msg;
    uint16_t id;
    byte_msg.resize(SIZE_16);
    socket.receiveBytes(byte_msg.data(), SIZE_16);
    memcpy(&id, byte_msg.data(), SIZE_16);
    return ntohs(id);
}

const std::vector<int> ClientProtocol::receiveBlocksAround() {
    std::vector<char> byte_msg;
    std::vector<int> blocks;
    byte_msg.resize(SIZE_16);
    socket.receiveBytes(byte_msg.data(), SIZE_16);

    blocks.resize(SIZE_16);
    blocks[0] = (int) byte_msg[0];
    blocks[1] = (int) byte_msg[1];

    return std::move(blocks);
}

matrix_t ClientProtocol::receiveMatrix() {
    matrix_t m;

    // Parte estatica
    std::vector<char> matrix_data_buffer(STATIC_TERRAIN_PART_SIZE, 0);
    socket.receiveBytes(matrix_data_buffer.data(), STATIC_TERRAIN_PART_SIZE);

    int bytes_advanced = 0;

    // Longitud del vector de terrenos
    uint16_t length;
    memcpy(&length, matrix_data_buffer.data() + bytes_advanced, SIZE_16);
    m.length = ntohs(length);
    bytes_advanced += SIZE_16;

    // Ancho de la matriz
    uint16_t width;
    memcpy(&width, matrix_data_buffer.data() + bytes_advanced, SIZE_16);
    m.width = ntohs(width);
    bytes_advanced += SIZE_16;

    // Alto de la matriz
    uint16_t height;
    memcpy(&height, matrix_data_buffer.data() + bytes_advanced, SIZE_16);
    m.height = ntohs(height);

    int matrix_length = m.length - HEIGHT_PLUS_WIDTH_SIZE;

    std::vector<char> matrix_buffer(matrix_length,0);
    socket.receiveBytes(matrix_buffer.data(), matrix_length);

    // Vector de terrenos
    std::vector<Terrain> terrains;
    terrains.resize(m.height * m.width);

    int i, current_index = 0;
    for (i = 0; i < m.height * m.width; i++) {
        auto terrain_type = (uint8_t) matrix_buffer[current_index];
        terrains[i] = static_cast<Terrain>(terrain_type);
        current_index++;
    }
    m.terrains = terrains;
    
    return std::move(m);
}

world_t ClientProtocol::receiveMessage() {
    world_t w;

    // Tipo de mensaje
    std::vector<char> message_type_buffer(SIZE_8, 0);
    socket.receiveBytes(message_type_buffer.data(), SIZE_8);

    if (debug) {
        std::cout << "Tipo de mensaje: \n";
        for (char& c : message_type_buffer)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }

    // Longitud del mensaje
    std::vector<char> length_buffer(SIZE_16, 0);
    socket.receiveBytes(length_buffer.data(), SIZE_16);

    if (debug) {
        std::cout << "Longitud de mensaje: \n";
        for (char& c : length_buffer)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }

    uint16_t length;
    memcpy(&length, length_buffer.data(), SIZE_16);
    w.length = ntohs(length);

    int bytes_advanced = 0;

    // Mensaje
    std::vector<char> world_buffer(w.length,0);
    socket.receiveBytes(world_buffer.data(), w.length);

    if (debug) {
        std::cout << "Mensaje: \n";
        for (char& c : world_buffer)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }

    // ---------------- //
    // Player principal //
    // ---------------- //

    // Vida actual
    uint16_t actual_life;
    memcpy(&actual_life, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.actual_life = ntohs(actual_life);
    bytes_advanced += SIZE_16;

    // Vida maxima
    uint16_t max_life;
    memcpy(&max_life, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.max_life = ntohs(max_life);
    bytes_advanced += SIZE_16;

    // Mana actual
    uint16_t actual_mana;
    memcpy(&actual_mana, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.actual_mana = ntohs(actual_mana);
    bytes_advanced += SIZE_16;

    // Mana maxima
    uint16_t max_mana;
    memcpy(&max_mana, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.max_mana = ntohs(max_mana);
    bytes_advanced += SIZE_16;

    // Oro actual
    uint16_t actual_gold;
    memcpy(&actual_gold, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.actual_gold = ntohs(actual_gold);
    bytes_advanced += SIZE_16;

    // Oro maximo
    uint16_t max_gold;
    memcpy(&max_gold, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.max_gold = ntohs(max_gold);
    bytes_advanced += SIZE_16;

    // Nivel
    uint16_t level;
    memcpy(&level, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.level = ntohs(level);
    bytes_advanced += SIZE_16;

    // Experiencia actual
    uint32_t actual_experience;
    memcpy(&actual_experience, world_buffer.data() + bytes_advanced, SIZE_32);
    w.player_info.actual_experience = ntohl(actual_experience);
    bytes_advanced += SIZE_32;

    if (debug) {
        std::cout << "\nPLAYER PRINCIPAL\n" <<
        "Vida actual: " << w.player_info.actual_life << "\n" <<
        "Vida maxima: " << w.player_info.max_life << "\n" <<
        "Mana actual: " << w.player_info.actual_mana << "\n" <<
        "Mana maxima: " << w.player_info.max_mana << "\n" <<
        "Oro actual: " << w.player_info.actual_gold << "\n" <<
        "Oro maximo: " << w.player_info.max_gold << "\n" <<
        "Nivel: " << w.player_info.level << "\n" <<
        "Experiencia actual: " << w.player_info.actual_experience << "\n" <<
        "Inventario:\n";
    }

    // Inventario
    uint8_t inventory_length;
    memcpy(&inventory_length, world_buffer.data() + bytes_advanced, SIZE_8);
    w.player_info.inventory.length = inventory_length;
    w.player_info.inventory.items.resize(inventory_length);
    bytes_advanced += SIZE_8;

    int i;
    for (i = 0; i < inventory_length; i ++) {
        uint8_t item_type;
        memcpy(&item_type, world_buffer.data() + bytes_advanced, SIZE_8);
        w.player_info.inventory.items[i] = item_type;
        bytes_advanced += SIZE_8;

        if (debug) {
            std::cout << "Item " << (i+1) << ": " <<
            w.player_info.inventory.items[i] << "\n";
        }
    }

    // ---------------- //
    // Lista de players //
    // ---------------- //

    // Cantidad de players
    uint16_t num_players;
    memcpy(&num_players, world_buffer.data() + bytes_advanced, SIZE_16);
    w.num_players = ntohs(num_players);
    bytes_advanced += SIZE_16;

    // Lista de players
    std::vector<player_t> players;
    players.resize(w.num_players);
    for (i = 0; i < w.num_players; i ++) {
        player_t player;

        // Id
        uint16_t id;
        memcpy(&id, world_buffer.data() + bytes_advanced, SIZE_16);
        player.id = ntohs(id);
        bytes_advanced += SIZE_16;

        // Pos x en la matriz
        uint16_t pos_x;
        memcpy(&pos_x, world_buffer.data() + bytes_advanced, SIZE_16);
        player.pos_x = ntohs(pos_x);
        bytes_advanced += SIZE_16;

        // Pos y en la matriz
        uint16_t pos_y;
        memcpy(&pos_y, world_buffer.data() + bytes_advanced, SIZE_16);
        player.pos_y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        // 1 si esta vivo, 0 si no (fantasma)
        uint8_t is_alive;
        memcpy(&is_alive, world_buffer.data() + bytes_advanced, SIZE_8);
        player.is_alive = is_alive;
        bytes_advanced += SIZE_8;

        // 1 si esta meditando, 0 si no
        uint8_t is_meditating;
        memcpy(&is_meditating, world_buffer.data() + bytes_advanced, SIZE_8);
        player.is_meditating = is_meditating;
        bytes_advanced += SIZE_8;

        // Enum type de la orientacion
        uint8_t orientation;
        memcpy(&orientation, world_buffer.data() + bytes_advanced, SIZE_8);
        player.orientation = orientation;
        bytes_advanced += SIZE_8;

        // Enum type de la raza
        uint8_t race_type;
        memcpy(&race_type, world_buffer.data() + bytes_advanced, SIZE_8);
        player.race_type = race_type;
        bytes_advanced += SIZE_8;

        // Enum type de la clase
        uint8_t class_type;
        memcpy(&class_type, world_buffer.data() + bytes_advanced, SIZE_8);
        player.class_type = class_type;
        bytes_advanced += SIZE_8;

        // Enum type del arma
        uint8_t weapon;
        memcpy(&weapon, world_buffer.data() + bytes_advanced, SIZE_8);
        player.weapon = weapon;
        bytes_advanced += SIZE_8;

        // Enum type de la armadura
        uint8_t armor;
        memcpy(&armor, world_buffer.data() + bytes_advanced, SIZE_8);
        player.armor = armor;
        bytes_advanced += SIZE_8;

        // Enum type del casco
        uint8_t helmet;
        memcpy(&helmet, world_buffer.data() + bytes_advanced, SIZE_8);
        player.helmet = helmet;
        bytes_advanced += SIZE_8;

        // Enum type del escudo
        uint8_t shield;
        memcpy(&shield, world_buffer.data() + bytes_advanced, SIZE_8);
        player.shield = shield;
        bytes_advanced += SIZE_8;

        players[i] = player;

        if (debug) {
            std::cout << "\nLISTA DE PLAYERS\n" <<
            "Id: " << player.id << "\n" <<
            "Pos X: " << player.pos_x << "\n" <<
            "Pos Y: " << player.pos_y << "\n" <<
            "Is alive: " << (int) player.is_alive << "\n" <<
            "Is meditating: " << (int) player.is_meditating << "\n" <<
            "Orientacion: " << (int) player.orientation << "\n" <<
            "Raza: " << (int) player.race_type << "\n" <<
            "Clase: " << (int) player.class_type << "\n" <<
            "Arma: " << (int) player.weapon << "\n" <<
            "Armadura: " << (int) player.armor << "\n" <<
            "Casco: " << (int) player.helmet << "\n" <<
            "Escudo: " << (int) shield << "\n";
        }
    }
    w.players = players;

    // ------------- //
    // Lista de NPCs //
    // ------------- //

    // TODO: ...

    // -------------- //
    // Lista de Items //
    // -------------- //

    // TODO: ...

    return std::move(w);
}
