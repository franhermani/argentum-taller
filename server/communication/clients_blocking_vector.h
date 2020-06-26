#ifndef BLOCKING_VECTOR_H
#define BLOCKING_VECTOR_H

#include <mutex>
#include <condition_variable>
#include <vector>

#include "../client_handler.h"

class ClientsBlockingVector {
private:
    std::mutex m;
    std::condition_variable cv;
    std::vector<ClientHandler*> clients;

public:
    // Constructor
    ClientsBlockingVector();

    // Constructor y asignacion por copia deshabilitados
    ClientsBlockingVector(const ClientsBlockingVector& other) = delete;
    ClientsBlockingVector& operator=(const ClientsBlockingVector& other)
            = delete;

    // Destructor
    ~ClientsBlockingVector();

    // Agrega un client handler al final del vector
    void add(ClientHandler* client);

    // Notifica al client cleaner que un cliente se desconecto
    void notifyClientsCleaner();

    // Remueve los dead client handlers del vector
    void removeDeadClients();

    // Joinea todos los client handlers del vector
    void joinClients();
};

#endif // BLOCKING_VECTOR_H
