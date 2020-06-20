#include <string>
#include <vector>
#include "protocol.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/debug.h"

#define BYTE_SIZE   1
#define SIZE_8      sizeof(uint8_t)
#define SIZE_16     sizeof(uint16_t)

ServerProtocol::ServerProtocol(Socket& socket) : socket(socket) {}

const std::string ServerProtocol::receiveUsername() {
    std::vector<char> arguments;
    char buffer1[BYTE_SIZE];
    socket.receiveBytes(buffer1, BYTE_SIZE);

    int length = buffer1[0];
    arguments.resize(length);
    socket.receiveBytes(arguments.data(), arguments.size());

    std::string username(arguments.begin(), arguments.end());

    if (debug)
        std::cout << "Recibido el username " << username << "\n";

    return username;
}

Command* ServerProtocol::receiveCommand(Player& player) {
    std::vector<char> arguments;
    char buffer1[BYTE_SIZE], buffer2[BYTE_SIZE];

    socket.receiveBytes(buffer1, BYTE_SIZE);
    socket.receiveBytes(buffer2, BYTE_SIZE);

    int type = buffer1[0], length = buffer2[0];

    if (debug)
        std::cout << "Recibido el comando tipo " << type <<
        " de longitud " << length << "\n";

    if (length > 0) {
        arguments.resize(length);
        socket.receiveBytes(arguments.data(), arguments.size());
    }
    return commandFactory(player, type, arguments);
}

void ServerProtocol::sendMatrix(WorldMonitor &world_monitor) {
    std::vector<std::vector<Terrain>> matrix = world_monitor.getMatrix();
    int width = world_monitor.getWidth();
    int height = world_monitor.getHeight();
    int matrix_length = width * height;

    matrix_t m;
    m.length = htons(2 * SIZE_16 + matrix_length * SIZE_8);
    m.width = htons(width);
    m.height = htons(height);

    std::vector<char> byte_msg;
    byte_msg.resize(3 * SIZE_16 + matrix_length);
    memcpy(&byte_msg[0], &m.length, SIZE_16);
    memcpy(&byte_msg[2], &m.width, SIZE_16);
    memcpy(&byte_msg[4], &m.height, SIZE_16);

    int i, j, k = 0;
    for (i = 0; i < height; i ++) {
        for (j = 0; j < width; j ++) {
            byte_msg[6+(k++)] = matrix[i][j];
        }
    }
    socket.sendBytes(byte_msg.data(), byte_msg.size());

    if (debug) {
        std::cout << "Matriz enviada: ";
        for (char& c : byte_msg)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }
}

void ServerProtocol::sendWorldAround(WorldMonitor& world_monitor,
        Player& player) {
    std::vector<Player*> players =
            world_monitor.getPlayersAround(player);

    int i;

    // Longitudes variables
    int inventory_length = 10;  // TODO: ...
    int num_players = players.size();
//    int num_npcs = npcs.size();
//    int num_items = items.size();

    // Longitud total del mensaje
    // TODO: completar con npcs e items
    int message_length =
            8 * SIZE_16 +
            SIZE_8 + inventory_length * SIZE_8 +
            SIZE_16 + num_players * (3 * SIZE_16 + 7 * SIZE_8);

    world_t w;

    // Longitud total mensaje
    w.length = htons(message_length);

    // Info particular del player del cliente
    w.player_info.actual_life = htons(player.actualLife);
    w.player_info.max_life = htons(player.maxLife);
    w.player_info.actual_mana = htons(player.actualMana);
    w.player_info.max_mana = htons(player.maxMana);
    w.player_info.actual_gold = htons(player.actualGold);
    w.player_info.max_gold = htons(player.maxGold);
    w.player_info.experience = htons(player.experience);
    w.player_info.level = htons(player.level);

    // Info generica de todos los players (incluido el del cliente)
    w.num_players = num_players;
    w.players.resize(num_players);
    for (i = 0; i < num_players; i ++) {
        w.players[i].id = htons(players[i]->id);
        w.players[i].pos_x = htons(players[i]->posX);
        w.players[i].pos_y = htons(players[i]->posY);
        w.players[i].is_alive = players[i]->isAlive ? 1 : 0;
        w.players[i].orientation = players[i]->orientation;
        w.players[i].race_type = players[i]->raceType;
        w.players[i].class_type = players[i]->classType;
        w.players[i].body_armor = players[i]->bodyArmor;
        w.players[i].head_armor = players[i]->headArmor;
        w.players[i].weapon = players[i]->weapon;
    }

    // TODO: completar con npcs e items
//    std::vector<NPC*> npc = world.getNPCsAround(player);
//    std::vector<Item*> items = world.getItemsAround(player);

    int pos = 0;
    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_16 + message_length);

    // Longitud total mensaje
    memcpy(&byte_msg[0], &w.length, SIZE_16);

    // Info particular del player del cliente
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.actual_life, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.max_life, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.actual_mana, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.max_mana, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.actual_gold, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.max_gold, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.experience, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.level, SIZE_16);

    // Inventario
    byte_msg[pos+=SIZE_16] = inventory_length;
    for (i = 0; i < inventory_length; i ++)
        byte_msg[pos+=SIZE_8] = i + 1;      // TODO: ...

    // Lista de players
    memcpy(&byte_msg[pos+=SIZE_16], &w.num_players, SIZE_16);
    pos -= SIZE_8;
    for (i = 0; i < num_players; i ++) {
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].id, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].pos_x, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].pos_y, SIZE_16);
        byte_msg[pos+=SIZE_16] = w.players[i].is_alive;
        byte_msg[pos+=SIZE_8] = w.players[i].orientation;
        byte_msg[pos+=SIZE_8] = w.players[i].race_type;
        byte_msg[pos+=SIZE_8] = w.players[i].class_type;
        byte_msg[pos+=SIZE_8] = w.players[i].body_armor;
        byte_msg[pos+=SIZE_8] = w.players[i].head_armor;
        byte_msg[pos+=SIZE_8] = w.players[i].weapon;
        pos -= SIZE_8;
    }
    socket.sendBytes(byte_msg.data(), byte_msg.size());

    if (debug) {
        std::cout << "Mundo enviado: ";
        for (char& c : byte_msg)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }
}
