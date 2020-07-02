#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include "connection_receiver.h"
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
        npcs_t npcs = protocol.receiveNPCs();

        // TODO: pasar por referencia
        mapMonitor.initialize(username_id, blocks_around,
                std::move(matrix), npcs);

        std::string game_message;

        while (keepRunning) {
            world_t world = protocol.receiveWorldUpdate();
            mapMonitor.updateWorld(std::move(world));

            // TODO: mandar estos al mapMonitor o gameRender en un struct
            protocol.receiveItemsList();

            game_message = protocol.receiveGameMessage();
            if (game_message.empty()) {
                // Do nothing
            }
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
