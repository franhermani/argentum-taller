#include <vector>
#include <utility>
#include "thread_acceptor.h"
#include "thread_client.h"
#include "../common/socket_accept_error.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port) :
        socket(host, port, true), keepTalking(true), isRunning(true) {}

void ThreadAcceptor::run() {
    while (keepTalking) {
        try {
            socket.listenToClients();
            createThreadClient();
            startThreadClient();
            cleanDeadClients();
        } catch(SocketAcceptError) {
            break;
        }
    }
    isRunning = false;
    joinClients();
}

void ThreadAcceptor::stop() {
    keepTalking = false;
    socket.finish();
}

const bool ThreadAcceptor::isDead() {
    return (! isRunning);
}

void ThreadAcceptor::createThreadClient() {
    Socket socket_client = socket.acceptClients();
    clients.push_back(new ThreadClient(std::move(socket_client)));
}

void ThreadAcceptor::startThreadClient() {
    clients.back()->start();
}

void ThreadAcceptor::cleanDeadClients() {
    std::vector<ThreadClient*> tmp;
    std::vector<ThreadClient*>::iterator iter = clients.begin();
    for (; iter != clients.end(); ++iter) {
        if ((*iter)->isDead()) {
            (*iter)->join();
            delete (*iter);
        } else {
            tmp.push_back((*iter));
        }
    }
    clients.swap(tmp);
}

void ThreadAcceptor::joinClients() {
    size_t i;
    for (i = 0; i < clients.size(); i ++) {
        clients[i]->join();
        delete clients[i];
    }
}
