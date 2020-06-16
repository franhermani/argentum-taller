#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <string>
#include "../../common/thread.h"
#include "protocol.h"

class ClientReceiver : public Thread {
    ServerProtocol protocol;
    World& world;
    Player* player{};

public:
    // Constructor
    ClientReceiver(Socket& socket, World& world);

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

    // Carga su atributo player
    void addPlayer(Player* new_player);
};

#endif // CLIENT_RECEIVER_H
