#include <string>
#include <vector>
#include "protocol.h"
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

    int type = buffer1[0];
    int length = buffer2[0];

    if (length > 0) {
        arguments.resize(length);
        socket.receiveBytes(arguments.data(), arguments.size());
    }
    return commandFactory(player, type, arguments);
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
