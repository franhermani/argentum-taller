#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket, World& world) :
protocol(socket), world(world) {
    keepRunning = true;
    isRunning = true;
}

void ClientSender::run() {
    /*
    while (keepRunning) {
        try {
            // TODO: enviar mapa actualizado al cliente
            protocol.sendWorldAround(world, player)
        } catch(SocketError&) {
            break;
        }
    }
    */
//    protocol.sendWorldAround(world, *player);

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
