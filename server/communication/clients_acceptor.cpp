#include <vector>
#include <utility>
#include "clients_acceptor.h"
#include "../../common/socket_accept_error.h"
#include "../../common/defines/username_confirmation.h"

ClientsAcceptor::ClientsAcceptor(const char *host, const char *port,
        GameManager& game_manager) : socket(host, port, true),
        gameManager(game_manager) {
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
        } catch (SocketAcceptError&) {
            break;
        } catch (DuplicatedUsernameException&) {
            // Do nothing
        } catch (NoMoreAvailableIdsException&) {
            // Do nothing
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
    clients.push_back(new ClientHandler(std::move(socket_client),gameManager));
}

void ClientsAcceptor::startClientHandler() {
    clients.back()->start();
}

void ClientsAcceptor::cleanDeadClientHandlers() {
    std::vector<ClientHandler*> tmp;
    auto iter = clients.begin();
    for (; iter != clients.end(); ++iter) {
        if ((*iter)->isDead()) {
            (*iter)->stop();
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
