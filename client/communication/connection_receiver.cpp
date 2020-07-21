#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, ClientWorldMonitor& worldMonitor) :
        protocol(socket), worldMonitor(worldMonitor) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    std::string message;

    try {
        int username_id = protocol.receiveUsernameId();
        std::vector<int> blocks_around = protocol.receiveBlocksAround();
        std::vector<int> map_dimensions = protocol.receiveMapDimensions();
        npcs_t npcs = protocol.receiveNPCs();

        worldMonitor.initialize(username_id, blocks_around, npcs, map_dimensions);

        while (keepRunning) {
            world_t world = protocol.receiveWorldUpdate();
            message = protocol.receiveGameMessage();
            printGameMessage(message);
            list_t list = protocol.receiveItemsList();
            worldMonitor.updateWorld(std::move(world), std::move(list));
        }
    } catch(SocketError&) {
        // Do nothing
    }
    isRunning = false;
}

void ConnectionReceiver::stop() {
    keepRunning = false;
}

bool ConnectionReceiver::isDead() {
    return (! isRunning);
}

const int ConnectionReceiver::receiveUsernameConfirmation() {
    return protocol.receiveUsernameConfirmation();
}

void ConnectionReceiver::printGameMessage(std::string& message) {
    if (message.empty())
        return;

    std::cout << "\n" << message << "\n";
}
