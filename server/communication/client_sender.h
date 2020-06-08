#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <atomic>
#include "../../common/thread.h"
#include "protocol.h"

class ClientSender : public Thread {
    ServerProtocol protocol;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;
    std::atomic<bool> isFinished;

public:
    // Constructor
    explicit ClientSender(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientSender(const ClientSender&) = delete;
    ClientSender& operator=(const ClientSender&) = delete;

    // Envia un mensaje segun el protocolo
    void run() override;

    // Setea la variable booleana 'keepTalking' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    const bool isDead() override;
};

#endif // CLIENT_SENDER_H
