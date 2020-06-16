#include <string>
#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, GameRender& gameRender) :
                protocol(socket), gameRender(gameRender) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {


    std::string message;

    while (keepRunning) {
        try {
            // TODO: recibo el mapa y actualizo el modelo local
            //std::vector<Terrain> terrains = protocol.receiveTerrains();
            //std::vector<npc_pos> npcs = protocol.receiveNpcs();
            //gameRender.play(terrains, npcs);
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


