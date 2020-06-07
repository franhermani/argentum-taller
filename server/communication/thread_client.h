#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include <atomic>
#include "../../common/thread.h"
#include "../../common/socket.h"

class ThreadClient : public Thread {
    Socket socket;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;
    std::atomic<bool> isFinished;

    // Interactua con los clientes (envia y recibe mensajes)
    void interactWithClient();

public:
    // Constructor
    explicit ThreadClient(Socket socket);

    // Constructor y asignacion por copia deshabilitados
    ThreadClient(const ThreadClient&) = delete;
    ThreadClient& operator=(const ThreadClient&) = delete;

    // Llama a interactWithClient hasta que finalice la partida
    virtual void run() override;

    // Setea la variable booleana 'keepTalking' en false
    virtual void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    virtual const bool isDead() override;
};

#endif // THREAD_CLIENT_H
