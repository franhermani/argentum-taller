#ifndef CONNECTION_SENDER_H
#define CONNECTION_SENDER_H

#include <string>
#include "../../common/thread.h"
#include "protocol.h"
#include "../../common/blocking_queue.h"
#include "../../common/commands/command.h"
class ConnectionSender : public Thread {
    ClientProtocol protocol;
    BlockingQueue<Command*>& commandQueue;

public:
    // Constructor
    ConnectionSender(Socket& socket, BlockingQueue<Command*>& commandQueue);

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

    // Envia el username del cliente para que el server lo identifique
    // Este metodo se llama antes de run()
    void sendUsername(const std::string& username);
};

#endif // CONNECTION_SENDER_H
