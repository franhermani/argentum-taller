#include <string>
#include <iostream>
#include "connection_sender.h"
#include "../../common/socket_error.h"
#include "../data_transfer_objects/attack_command_dto.h"

ConnectionSender::ConnectionSender(Socket& socket,
        BlockingQueue<CommandDTO*>& commandQueue) : protocol(socket),
        commandQueue(commandQueue) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionSender::run() {
    auto* cmd = new AttackCommandDTO(12345);
    protocol.sendCommand(*cmd);
    while (keepRunning) {
        try {
            CommandDTO* command = commandQueue.pop();
            protocol.sendCommand(*command);
            delete command;
        } catch(SocketError&) {
            break;
        } catch (ClosedQueueException&) {
            break;
        }
    }

    isRunning = false;
}

void ConnectionSender::stop() {
    keepRunning = false;
}

bool ConnectionSender::isDead() {
    return (! isRunning);
}

void ConnectionSender::sendUsername(const std::string& username) {
    protocol.sendUsername(username);
}
