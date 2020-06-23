#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, GameRender& gameRender, MapMonitor& mapMonitor) :
                protocol(socket), gameRender(gameRender), mapMonitor(mapMonitor) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    //en realidad esto de inicializar tambien deberia estar en un try
    matrix_t matrix = protocol.receiveMatrix(gameRender);
    mapMonitor.initializeMatrix(matrix);
    while (keepRunning) {
        try {
            world_t world = protocol.receiveWorld();
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
