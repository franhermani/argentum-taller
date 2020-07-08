#ifndef PROTECTED_QUEUE_H
#define PROTECTED_QUEUE_H

#include <exception>
#include <mutex>
#include <queue>
#include <string>
#include "../server/game/commands/command.h"
#include "defines/world_structs.h"

struct ClosedQueueException : public std::exception {
    const char* what() const throw() {
        return "The queue is closed\n";
    }
};

template <class T> class ProtectedQueue {
private:
    std::mutex m;
    std::queue<T> queue;
    bool isClosed;

public:
    // Constructor
    ProtectedQueue();

    // Constructor y asignacion por copia deshabilitados
    ProtectedQueue(const ProtectedQueue& other) = delete;
    ProtectedQueue& operator=(const ProtectedQueue& other) = delete;

    // Destructor
    ~ProtectedQueue();

    // Agrega un elemento a la cola
    void push(T t);

    // Quita el elemento mas antiguo de la cola
    T pop();

    // Cierra la cola
    void close();

    // Devuelve true si la cola esta vacia, false en caso contrario
    bool isEmpty();
};

// Definir aca los tipos T que usemos a lo largo del TP
template class ProtectedQueue<Command*>;
template class ProtectedQueue<std::string>;
template class ProtectedQueue<list_t>;

#endif // PROTECTED_QUEUE_H
