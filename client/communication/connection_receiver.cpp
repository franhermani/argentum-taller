#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, GameRender& gameRender) :
                protocol(socket), gameRender(gameRender) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    //en realidad esto de inicializar tambien deberia estar en un try
    protocol.initializeMap(gameRender);

    while (keepRunning) {
        try {
            protocol.receiveWorld(gameRender);
            //std::vector<npc_pos> npcs = protocol.receiveNpcs();
            //gameRender.renderNpcs(npcs);
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
