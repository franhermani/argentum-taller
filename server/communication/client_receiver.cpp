#include <vector>
#include "client_receiver.h"
#include "../../common/socket_error.h"

ClientReceiver::ClientReceiver(Socket& socket,
        ProtectedQueue<Command*>& command_queue) :
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

const std::vector<char> ClientReceiver::receivePlayerInfo() {
    return protocol.receivePlayerInfo();
}

void ClientReceiver::setPlayer(Player* new_player) {
    player = new_player;
}
