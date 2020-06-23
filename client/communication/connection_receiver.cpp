#include <iostream>
#include <utility>
#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, MapMonitor& mapMonitor) :
                protocol(socket), mapMonitor(mapMonitor) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    try {
        protocol.receiveUsernameId();
        protocol.receiveBlocksAround();
        matrix_t matrix = protocol.receiveMatrix();
        mapMonitor.initializeMatrix(std::move(matrix));
        while (keepRunning) {
            world_t world = protocol.receiveWorld();
            mapMonitor.updateWorld(std::move(world));
        }
    } catch(SocketError&) {
        // TODO ver que hacer aca
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

