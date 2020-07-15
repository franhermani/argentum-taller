#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <string>
#include "../../common/thread.h"
#include "protocol.h"
#include "../game/world_monitor.h"
#include "../../common/protected_queue.h"

class ClientSender : public Thread {
    ServerProtocol protocol;
    WorldMonitor* worldMonitor;
    ProtectedQueue<std::string>* messagesQueue;
    ProtectedQueue<list_t>* listsQueue;
    int msPerSend, minMsSleep;
    Player* player{};

public:
    // Constructor
    ClientSender(Socket& socket, WorldMonitor* worldMonitor,
            ProtectedQueue<std::string>* messages_queue,
            ProtectedQueue<list_t>* lists_queue, int ms_per_send,
            int min_ms_sleep);

    // Constructor utilizado cuando el username ya existe
    explicit ClientSender(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientSender(const ClientSender&) = delete;
    ClientSender& operator=(const ClientSender&) = delete;

    // Envia un mensaje segun el protocolo
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;

    // Envia un codigo de confirmacion del username al cliente
    void sendUsernameConfirmation(int code);

    // Setea el atributo 'player'
    void setPlayer(Player* player);
};

#endif // CLIENT_SENDER_H
