#include <vector>
#include <utility>
#include "clients_acceptor.h"
#include "client_receiver.h"
#include "../../common/socket_accept_error.h"

ClientsAcceptor::ClientsAcceptor(const char *host, const char *port) :
socket(host, port, true) {
    keepRunning = true;
    isRunning = true;
}

void ClientsAcceptor::run() {
    while (keepRunning) {
        try {
            socket.listenToClients();
            createClientHandler();
            startClientHandler();
            cleanDeadClientHandlers();
        } catch(SocketAcceptError&) {
            break;
        }
    }
    isRunning = false;
    joinClientHandlers();
}

void ClientsAcceptor::stop() {
    keepRunning = false;
    socket.finish();
}

bool ClientsAcceptor::isDead() {
    return (! isRunning);
}

void ClientsAcceptor::createClientHandler() {
    Socket socket_client = socket.acceptClients();
    clients.push_back(new ClientHandler(std::move(socket_client)));
}

void ClientsAcceptor::startClientHandler() {
    clients.back()->start();
}

void ClientsAcceptor::cleanDeadClientHandlers() {
    std::vector<ClientHandler*> tmp;
    auto iter = clients.begin();
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

void ClientsAcceptor::joinClientHandlers() {
    size_t i;
    for (i = 0; i < clients.size(); i ++) {
        clients[i]->stop();
        clients[i]->join();
        delete clients[i];
    }
}
