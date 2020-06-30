#include <iostream>
#include <utility>
#include "connection_receiver.h"
#include <vector>
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, MapMonitor& mapMonitor) :
                protocol(socket), mapMonitor(mapMonitor) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    try {
        int username_id = protocol.receiveUsernameId();
        std::vector<int> blocks_around = protocol.receiveBlocksAround();
        matrix_t matrix = protocol.receiveMatrix();

        // TODO: pasarle npcs al initialize
        npcs_t npcs = protocol.receiveNPCs();
        mapMonitor.updateNpcs(npcs);

        // TODO: pasar por referencia
        mapMonitor.initialize(username_id, blocks_around, std::move(matrix));

        while (keepRunning) {
            world_t world = protocol.receiveMessage();
            mapMonitor.updateWorld(std::move(world));
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
