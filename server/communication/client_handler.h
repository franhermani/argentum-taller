#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <atomic>
#include "../../common/thread.h"
#include "../../common/socket.h"
#include "client_sender.h"
#include "client_receiver.h"

class ClientHandler : public Thread {
    Socket socket;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;
    std::atomic<bool> isFinished;
    ClientSender* clientSender;
    ClientReceiver* clientReceiver;

public:
    // Constructor
    explicit ClientHandler(Socket socket);

    // Constructor y asignacion por copia deshabilitados
    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

    // Destructor
    // Elimina la memoria reservada para los thread sender y receiver
    ~ClientHandler();

    // ...
    void run() override;

    // Setea la variable booleana 'keepTalking' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // CLIENT_HANDLER_H
