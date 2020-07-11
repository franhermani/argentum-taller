#include <string>
#include <chrono>
#include "client_sender.h"
#include "../../common/socket_error.h"

ClientSender::ClientSender(Socket& socket, WorldMonitor* world_monitor,
        ProtectedQueue<std::string>* messages_queue,
        ProtectedQueue<list_t>* lists_queue, int ms_per_send) :
        protocol(socket), worldMonitor(world_monitor),
        messagesQueue(messages_queue), listsQueue(lists_queue),
        msPerSend(ms_per_send) {
    keepRunning = true;
    isRunning = true;
}

ClientSender::ClientSender(Socket& socket) : protocol(socket) {
    keepRunning = true;
    isRunning = true;
}

// TODO: modularizar esta funcion
void ClientSender::run() {
    using ms = std::chrono::milliseconds;

    try {
        // Envio el ID para que el cliente lo almacene
        protocol.sendUsernameId(*player);

        // Envio la vision para que el cliente sepa cuanto renderizar
        protocol.sendBlocksAround(worldMonitor->getPlayerWidth(),
                worldMonitor->getPlayerHeight());

        // Envio la matriz completa con todos los terrenos
        protocol.sendMatrix(*worldMonitor);

        // Envio la lista de NPCs
        protocol.sendNPCs(*worldMonitor);

        // Excepciones del juego
        std::string game_message, empty_message = "";

        // Respuesta al comando Listar
        list_t list, empty_list;
        empty_list.show_price = 0;
        empty_list.gold_quantity = 0;
        empty_list.num_items = 0;

        // Envio actualizaciones del juego
        while (keepRunning) {
            std::this_thread::sleep_for(ms(msPerSend));

            // Envio actualizaciones del mundo
            protocol.sendWorldUpdate(*worldMonitor, *player);

            // Envio excepciones del juego
            if (! messagesQueue->isEmpty()) {
                try {
                    game_message = messagesQueue->pop();
                    protocol.sendGameMessage(game_message);
                } catch (ClosedQueueException&) {
                    break;
                }
            } else {
                protocol.sendGameMessage(empty_message);
            }

            // Envio respuesta al comando listar
            if (! listsQueue->isEmpty()) {
                try {
                    list = listsQueue->pop();
                    protocol.sendItemsList(list);
                } catch (ClosedQueueException&) {
                    break;
                }
            } else {
                protocol.sendItemsList(empty_list);
            }
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
