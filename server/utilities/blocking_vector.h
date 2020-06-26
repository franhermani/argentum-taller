#ifndef BLOCKING_VECTOR_H
#define BLOCKING_VECTOR_H

#include <mutex>
#include <condition_variable>
#include <vector>

#include "../client_handler.h"

class BlockingVector {
private:
    std::mutex m;
    std::condition_variable cv;
    std::vector<ClientHandler*> clients;

public:
    // Constructor
    BlockingVector();

    // Constructor y asignacion por copia deshabilitados
    BlockingVector(const BlockingVector& other) = delete;
    BlockingVector& operator=(const BlockingVector& other) = delete;

    // Destructor
    ~BlockingVector();

    // Agrega un client handler al final del vector
    void add(ClientHandler* client);

    // Remueve los dead client handlers del vector
    void removeDeadClients();

    // Joinea todos los client handlers del vector
    void joinClients();
};

#endif // BLOCKING_VECTOR_H
