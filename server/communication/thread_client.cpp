#include <utility>
#include "thread_client.h"
#include "../../common/socket_error.h"

ThreadClient::ThreadClient(Socket socket) : socket(std::move(socket)),
        keepTalking(true), isRunning(true), isFinished(false) {}

void ThreadClient::run() {
    while (keepTalking) {
        try {
            interactWithClient();
        } catch(SocketError) {
            break;
        }
    }
    isRunning = false;
}

void ThreadClient::stop() {
    keepTalking = false;
}

const bool ThreadClient::isDead() {
    return (! isRunning);
}

void ThreadClient::interactWithClient() {
//    std::string response = receiveMessage();
//    sendMessage(response);
    isFinished = true;
    if (isFinished) stop();
}
