#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket, World& world) :
protocol(socket), world(world) {
    keepRunning = true;
    isRunning = true;
}

void ClientSender::run() {
    while (keepRunning) {
        try {
            // TODO: ver si se envia constantemente o hay alguna cv
//            protocol.sendWorldAround(world, *player);
        } catch(SocketError&) {
            break;
        }
    }
    isRunning = false;
}

void ClientSender::stop() {
    keepRunning = false;
}

bool ClientSender::isDead() {
    return (! isRunning);
}

void ClientSender::addPlayer(Player* new_player) {
    player = new_player;
}
