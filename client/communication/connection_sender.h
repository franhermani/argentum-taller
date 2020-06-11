#ifndef CONNECTION_SENDER_H
#define CONNECTION_SENDER_H

#include "../../common/thread.h"
#include "protocol.h"

class ConnectionSender : public Thread {
    ClientProtocol protocol;

public:
    // Constructor
    explicit ConnectionSender(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ConnectionSender(const ConnectionSender&) = delete;
    ConnectionSender& operator=(const ConnectionSender&) = delete;

    // Envia un mensaje segun el protocolo
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // CONNECTION_SENDER_H
