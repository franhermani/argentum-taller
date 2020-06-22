#include <string>
#include <iostream>
#include "connection_sender.h"
#include "../../common/socket_error.h"

ConnectionSender::ConnectionSender(Socket& socket,
        BlockingQueue<CommandDTO*>& commandQueue) : protocol(socket),
        commandQueue(commandQueue) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionSender::run() {
    while (keepRunning) {
        try {
            CommandDTO *command = commandQueue.pop();
            protocol.sendCommand(*command);
            delete command;
        } catch (SocketError&) {
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

void ConnectionSender::sendPlayerInfo(const std::string &username,
        const uint8_t race_type, const uint8_t class_type) {
    protocol.sendPlayerInfo(username, race_type, class_type);
}
