#include <chrono>
#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket, WorldMonitor& world_monitor,
        int ms_per_send) : protocol(socket), worldMonitor(world_monitor),
        msPerSend(ms_per_send) {
    keepRunning = true;
    isRunning = true;
}

void ClientSender::run() {
    using ms = std::chrono::milliseconds;

    // Envio el ID para que el cliente lo almacene
    protocol.sendUsernameId(*player);

    // Envio la vision para que el cliente sepa cuanto renderizar
    protocol.sendBlocksAround(worldMonitor.getPlayerWidth(),
            worldMonitor.getPlayerHeight());

    // Envio la matriz completa con todos los terrenos
    protocol.sendMatrix(worldMonitor);

    // Envio actualizaciones del mundo
    while (keepRunning) {
        try {
            std::this_thread::sleep_for(ms(msPerSend));
            protocol.sendWorldAround(worldMonitor, *player);
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

void ClientSender::sendUsernameConfirmation(int code) {
    protocol.sendUsernameConfirmation(code);
}

void ClientSender::setPlayer(Player* new_player) {
    player = new_player;
}
