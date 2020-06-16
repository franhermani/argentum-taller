#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include "../../common/thread.h"
#include "protocol.h"

class ClientSender : public Thread {
    ServerProtocol protocol;
    World& world;
    Player* player{};

public:
    // Constructor
    ClientSender(Socket& socket, World& world);

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

    // Carga su atributo player
    void addPlayer(Player* new_player);
};

#endif // CLIENT_SENDER_H
