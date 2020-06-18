#include <string>
#include "client_receiver.h"
#include "../../common/socket_error.h"

ClientReceiver::ClientReceiver(Socket& socket,
        BlockingQueue<Command*>& command_queue) :
        protocol(socket), commandQueue(command_queue) {
    keepRunning = true;
    isRunning = true;
}

void ClientReceiver::run() {
    while (keepRunning) {
        try {
            Command* command = protocol.receiveCommand(*player);
            commandQueue.push(command);
        } catch(SocketError&) {
            break;
        }
    }
    isRunning = false;
}

void ClientReceiver::stop() {
    keepRunning = false;
}

bool ClientReceiver::isDead() {
    return (! isRunning);
}

const std::string ClientReceiver::receiveUsername() {
    return protocol.receiveUsername();
}

void ClientReceiver::setPlayer(Player* new_player) {
    player = new_player;
}
