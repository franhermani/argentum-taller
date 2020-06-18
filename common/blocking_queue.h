#ifndef TP2_BLOCKING_QUEUE_H
#define TP2_BLOCKING_QUEUE_H

#include <exception>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "data_transfer_objects/command_dto.h"
#include "../server/game/commands/command.h"

struct ClosedQueueException : public std::exception {
    const char* what() const throw() {
        return "The queue is closed\n";
    }
};

template <class T> class BlockingQueue {
private:
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;
    bool isClosed;

public:
    // Constructor
    BlockingQueue();

    // Constructor y asignacion por copia deshabilitados
    BlockingQueue(const BlockingQueue& other) = delete;
    BlockingQueue& operator=(const BlockingQueue& other) = delete;

    // Destructor
    ~BlockingQueue();

    // Agrega un elemento a la cola
    void push(T t);

    // Quita el elemento mas antiguo de la cola
    T pop();

    // Cierra la cola
    void close();
};

// Definir aca los tipos T que usemos a lo largo del TP
template class BlockingQueue<Command*>;
template class BlockingQueue<CommandDTO*>;

#endif //TP2_BLOCKING_QUEUE_H
