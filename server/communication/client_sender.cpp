#include <chrono>
#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket, WorldMonitor& world_monitor,
        Player& player, int ms_per_send) : protocol(socket),
        worldMonitor(world_monitor), player(player), msPerSend(ms_per_send) {
    keepRunning = true;
    isRunning = true;
}

void ClientSender::run() {
    using ms = std::chrono::milliseconds;

    while (keepRunning) {
        try {
            std::this_thread::sleep_for(ms(msPerSend));
            protocol.sendWorldAround(worldMonitor, player);
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
