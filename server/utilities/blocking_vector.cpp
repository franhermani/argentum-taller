#include <vector>
#include "blocking_vector.h"

BlockingVector::BlockingVector() = default;

BlockingVector::~BlockingVector() = default;

void BlockingVector::add(ClientHandler* client) {
    std::unique_lock<std::mutex> lk(m);
    clients.push_back(client);
}

void BlockingVector::notifyClientsCleaner() {
    cv.notify_all();
}

void BlockingVector::removeDeadClients() {
    std::unique_lock<std::mutex> lk(m);

    if (clients.empty()) return;

    cv.wait(lk);
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

void BlockingVector::joinClients() {
    std::unique_lock<std::mutex> lk(m);
    if (clients.empty()) return;

    size_t i;
    for (i = 0; i < clients.size(); i ++) {
        clients[i]->stop();
        clients[i]->join();
        delete clients[i];
    }
}
