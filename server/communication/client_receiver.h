#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <vector>
#include "../../common/thread.h"
#include "protocol.h"
#include "../game/world_monitor.h"
#include "../../common/protected_queue.h"

class ClientReceiver : public Thread {
    ServerProtocol protocol;
    ProtectedQueue<Command*>& commandQueue;
    Player* player{};

public:
    // Constructor
    ClientReceiver(Socket& socket, ProtectedQueue<Command*>& command_queue);

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

    // Recibe la info del player del cliente
    // Este metodo se llama antes de run()
    const std::vector<char> receivePlayerInfo();

    // Setea el atributo 'player'
    void setPlayer(Player* player);
};

#endif // CLIENT_RECEIVER_H
