#include <string>
#include <vector>
#include "protocol.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/debug.h"

#define BYTE_SIZE 1

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
    m.length = htons(2*sizeof(uint16_t) + matrix_length*sizeof(uint8_t));
    m.width = htons(width);
    m.height = htons(height);

    std::vector<char> byte_msg;
    byte_msg.resize(3*sizeof(uint16_t) + matrix_length);
    memcpy(&byte_msg[0], &m.length, sizeof(uint16_t));
    memcpy(&byte_msg[2], &m.width, sizeof(uint16_t));
    memcpy(&byte_msg[4], &m.height, sizeof(uint16_t));

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
    std::vector<std::vector<Terrain>> matrix =
            world_monitor.getMatrixAround(player);
    std::vector<Player*> players =
            world_monitor.getPlayersAround(player);

    // TODO: ...
//    std::vector<NPC*> npc = world.getNPCsAround(player);
//    std::vector<Item*> items = world.getItemsAround(player);

//    std::vector<char> byte_msg = ...;
//    socket.sendBytes(byte_msg.data(), byte_msg.size());
}
