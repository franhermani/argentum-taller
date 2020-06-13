#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <string>
#include "../../common/thread.h"
#include "protocol.h"

class ClientReceiver : public Thread {
    ServerProtocol protocol;

public:
    // Constructor
    explicit ClientReceiver(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientReceiver(const ClientReceiver&) = delete;
    ClientReceiver& operator=(const ClientReceiver&) = delete;

    // Recibe un mensaje segun el protocolo
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;

    // Recibe el username del cliente para identificarlo
    // Este metodo se llama antes de run()
    const std::string receiveUsername();
};

#endif // CLIENT_RECEIVER_H
