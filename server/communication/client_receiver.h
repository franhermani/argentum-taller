#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <string>
#include "../../common/thread.h"
#include "protocol.h"
#include "../game/world_monitor.h"
#include "../../common/blocking_queue.h"

class ClientReceiver : public Thread {
    ServerProtocol protocol;
    BlockingQueue<Command*>& commandQueue;
    Player* player;

public:
    // Constructor
    ClientReceiver(Socket& socket, BlockingQueue<Command*>& command_queue);

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

    // Setea el atributo 'player'
    void setPlayer(Player* player);
};

#endif // CLIENT_RECEIVER_H
