#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <atomic>
#include "../../common/thread.h"
#include "../../common/socket.h"
#include "connection_sender.h"
#include "connection_receiver.h"

class ConnectionHandler : public Thread {
    Socket socket;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;
    std::atomic<bool> isFinished;
    ConnectionSender* connectionSender;
    ConnectionReceiver* connectionReceiver;

public:
    // Constructor
    explicit ConnectionHandler(const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    ConnectionHandler(const ConnectionHandler&) = delete;
    ConnectionHandler& operator=(const ConnectionHandler&) = delete;

    // Destructor
    // Elimina la memoria reservada para los thread sender y receiver
    ~ConnectionHandler();

    // Inicializa los thread sender y receiver
    void run() override;

    // Setea la variable booleana 'keepTalking' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // CONNECTION_HANDLER_H
