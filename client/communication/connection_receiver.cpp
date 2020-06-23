#include <iostream>
#include <chrono>
#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, MapMonitor& mapMonitor) :
                protocol(socket), mapMonitor(mapMonitor) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    //en realidad esto de inicializar tambien deberia estar en un try
    matrix_t matrix = protocol.receiveMatrix();
    mapMonitor.initializeMatrix(std::move(matrix));
    while (keepRunning) {
        try {
            world_t world = protocol.receiveWorld();
            mapMonitor.updateWorld(std::move(world));
        } catch(SocketError&) {
            break;
        }
    }
    isRunning = false;
}

void ConnectionReceiver::stop() {
    keepRunning = false;
}

bool ConnectionReceiver::isDead() {
    return (! isRunning);
}
