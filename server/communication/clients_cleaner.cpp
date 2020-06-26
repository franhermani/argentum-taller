#include "clients_cleaner.h"

ClientsCleaner::ClientsCleaner(ClientsBlockingVector& clients) :
clients(clients) {
    keepRunning = true;
    isRunning = true;
}

void ClientsCleaner::run() {
    while (keepRunning)
        clients.removeDeadClients();

    isRunning = false;
}

void ClientsCleaner::stop() {
    keepRunning = false;
    clients.joinClients();
}

bool ClientsCleaner::isDead() {
    return (! isRunning);
}
