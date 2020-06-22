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

    protocol.sendMatrix(worldMonitor);

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
