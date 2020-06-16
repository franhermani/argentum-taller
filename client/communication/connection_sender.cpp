#include <string>
#include <iostream>
#include "connection_sender.h"
#include "../../common/socket_error.h"
#include "../../common/commands/username_command.h"

ConnectionSender::ConnectionSender(Socket& socket,
        BlockingQueue<Command*>& commandQueue) : protocol(socket), commandQueue(commandQueue) {
    keepRunning = true;
    isRunning = true;
}

void ConnectionSender::run() {


    std::string message;

    while (keepRunning) {
        try {
            Command* command = commandQueue.pop();
            protocol.sendCommand(*command);
            delete command;

        } catch(SocketError&) {
            break;
        }
        catch (ClosedQueueException&) {
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
    UsernameCommand usernameCommand(username);
    protocol.sendCommand(usernameCommand);
}
