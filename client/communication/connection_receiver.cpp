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
    std::cout << "\n\n YA RECIBI MATRIZ Y LA GUARDO\n\n";
    mapMonitor.initializeMatrix(matrix);
    while (keepRunning) {
        try {
            world_t world = protocol.receiveWorld();
            std::cout << "\n\n estoy updateando players\n\n";
            mapMonitor.updateWorld(world);
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
