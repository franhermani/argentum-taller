#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <atomic>
#include "../../common/thread.h"
#include "../../common/socket.h"

class ClientReceiver : public Thread {
    Socket& socket;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;
    std::atomic<bool> isFinished;

public:
    // Constructor
    explicit ClientReceiver(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientReceiver(const ClientReceiver&) = delete;
    ClientReceiver& operator=(const ClientReceiver&) = delete;

    // ...
    void run() override;

    // Setea la variable booleana 'keepTalking' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    const bool isDead() override;
};

#endif // CLIENT_RECEIVER_H
