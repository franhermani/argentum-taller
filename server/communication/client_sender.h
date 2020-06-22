#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include "../../common/thread.h"
#include "protocol.h"
#include "../game/world_monitor.h"

class ClientSender : public Thread {
    ServerProtocol protocol;
    WorldMonitor& worldMonitor;
    int msPerSend;
    Player* player{};

public:
    // Constructor
    ClientSender(Socket& socket, WorldMonitor& worldMonitor, int ms_per_send);

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

    // Setea el atributo 'player'
    void setPlayer(Player* player);
};

#endif // CLIENT_SENDER_H
