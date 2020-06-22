#ifndef CONNECTION_SENDER_H
#define CONNECTION_SENDER_H

#include <string>
#include "../../common/thread.h"
#include "protocol.h"
#include "../../common/blocking_queue.h"

class ConnectionSender : public Thread {
    ClientProtocol protocol;
    BlockingQueue<CommandDTO*>& commandQueue;

public:
    // Constructor
    ConnectionSender(Socket& socket, BlockingQueue<CommandDTO*>& commandQueue);

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

    // Envia la informacion del player al server
    // Este metodo se llama antes de run()
    void sendPlayerInfo(const std::string& username, const uint8_t race_type,
            const uint8_t class_type);
};

#endif // CONNECTION_SENDER_H
