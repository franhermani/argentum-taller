#include <vector>
#include <utility>
#include "clients_acceptor.h"
#include "../../common/socket_accept_error.h"
#include "../../common/defines/username_confirmation.h"

ClientsAcceptor::ClientsAcceptor(const char *host, const char *port,
        GameManager& game_manager) : socket(host, port, true),
        gameManager(game_manager) {
    clientsCleaner = new ClientsCleaner(clients);
    keepRunning = true;
    isRunning = true;
}

ClientsAcceptor::~ClientsAcceptor() {
    delete clientsCleaner;
}

void ClientsAcceptor::run() {
    clientsCleaner->start();

    while (keepRunning) {
        try {
            socket.listenToClients();
            Socket socket_client = socket.acceptClients();
            auto new_client = new ClientHandler(std::move(socket_client),
                    gameManager);
            new_client->start();
            clients.add(new_client);
        } catch (SocketAcceptError&) {
            break;
        } catch (DuplicatedUsernameException&) {
            // Do nothing
        } catch (NoMoreAvailableIdsException&) {
            // Do nothing
        }
    }
    isRunning = false;
    clientsCleaner->stop();
    clientsCleaner->join();
    clients.joinClients();
}

void ClientsAcceptor::stop() {
    keepRunning = false;
    socket.finish();
}

bool ClientsAcceptor::isDead() {
    return (! isRunning);
}
