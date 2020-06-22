#ifndef CONNECTION_RECEIVER_H
#define CONNECTION_RECEIVER_H

#include "../../common/thread.h"
#include "protocol.h"
#include "../game/game_render.h"

class ConnectionReceiver : public Thread {
    ClientProtocol protocol;
    GameRender& gameRender;

public:
    // Constructor
    explicit ConnectionReceiver(Socket& socket, GameRender& gameRender);

    // Constructor y asignacion por copia deshabilitados
    ConnectionReceiver(const ConnectionReceiver&) = delete;
    ConnectionReceiver& operator=(const ConnectionReceiver&) = delete;

    // Recibe un mensaje segun el protocolo
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;

    // Recibe el codigo de confirmacion del server por el username enviado
    const int receiveUsernameConfirmation();
};

#endif // CONNECTION_RECEIVER_H
