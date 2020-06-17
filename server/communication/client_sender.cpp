#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket, WorldMonitor& world_monitor,
        Player& player) : protocol(socket), worldMonitor(world_monitor),
        player(player) {
    keepRunning = true;
    isRunning = true;
}

void ClientSender::run() {
    while (keepRunning) {
        try {
            // TODO: agregar un loop por tiempo como el del GameManager
//            protocol.sendWorldAround(worldMonitor, *player);
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
