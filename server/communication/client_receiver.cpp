#include <string>
#include "client_receiver.h"
#include "../../common/socket_error.h"
#include "../../common/commands/username_command.h"

ClientReceiver::ClientReceiver(Socket& socket, World& world) :
protocol(socket), world(world) {
    keepRunning = true;
    isRunning = true;
}

void ClientReceiver::run() {
    /*
    std::string message;

    while (keepRunning) {
        try {
            // TODO: recibir un comando del client y actualizar el mapa
            message = protocol.receiveCommand();
            world.update()
        } catch(SocketError&) {
            break;
        }
    }
     */
    Command* command = protocol.receiveCommand();
//    command->execute(*player);
    delete command;

    isRunning = false;
}

void ClientReceiver::stop() {
    keepRunning = false;
}

bool ClientReceiver::isDead() {
    return (! isRunning);
}

const std::string ClientReceiver::receiveUsername() {
    auto* command = dynamic_cast<UsernameCommand*>(protocol.receiveCommand());
    std::string username = command->getUsername();
    delete command;
    return username;
}

void ClientReceiver::addPlayer(Player* new_player) {
    player = new_player;
}
