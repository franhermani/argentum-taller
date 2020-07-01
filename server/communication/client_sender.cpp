#include <string>
#include <chrono>
#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket, WorldMonitor& world_monitor,
        ProtectedQueue<std::string>& messages_queue, int ms_per_send) :
        protocol(socket), worldMonitor(world_monitor),
        messagesQueue(messages_queue), msPerSend(ms_per_send) {
    keepRunning = true;
    isRunning = true;
}

void ClientSender::run() {
    using ms = std::chrono::milliseconds;

    try {
        // Envio el ID para que el cliente lo almacene
        protocol.sendUsernameId(*player);

        // Envio la vision para que el cliente sepa cuanto renderizar
        protocol.sendBlocksAround(worldMonitor.getPlayerWidth(),
                worldMonitor.getPlayerHeight());

        // Envio la matriz completa con todos los terrenos
        protocol.sendMatrix(worldMonitor);

        // Envio la lista de NPCs
        protocol.sendNPCs(worldMonitor);

        std::string game_message;

        // Envio actualizaciones del juego
        while (keepRunning) {
            std::this_thread::sleep_for(ms(msPerSend));
            protocol.sendWorldUpdate(worldMonitor, *player);

            // Desencolo de a un mensaje para que el player llegue a verlo
            if (! messagesQueue.isEmpty()) {
                try {
                    game_message = messagesQueue.pop();
                    protocol.sendGameMessage(game_message, *player);
                } catch (ClosedQueueException&) {
                    break;
                }
            } else {
                protocol.sendGameMessage("", *player);
            }
            // TODO: desencolar esto de algun lado
            protocol.sendItemsList(worldMonitor, *player);
        }
    } catch (SocketError&) {
        // Do nothing
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
