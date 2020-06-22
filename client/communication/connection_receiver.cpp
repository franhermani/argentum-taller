#include "connection_receiver.h"
#include "../../common/socket_error.h"

ConnectionReceiver::ConnectionReceiver(Socket& socket, GameRender& gameRender) :
                protocol(socket), gameRender(gameRender) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionReceiver::run() {
    try {
        protocol.initializeMap(gameRender);

        while (keepRunning) {
                protocol.receiveWorld(gameRender);
        }
    }catch(SocketError&) {
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
