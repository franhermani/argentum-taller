#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/blocking_queue.h"
#include "connection_sender.h"
#include "connection_receiver.h"
#include "game_render.h"
#include "gameplay.h"


class GameHandler : public Thread {
    Socket socket;

    //send related classes
    ConnectionSender* connectionSender;
    Gameplay* gameplay;
    BlockingQueue<Command*> commandQueue;

    //receive related classes
    ConnectionReceiver* connectionReceiver;
    GameRender gameRender;

public:
    // Constructor
    explicit GameHandler(const char *host, const char *port, const char *username);

    // Constructor y asignacion por copia deshabilitados
    GameHandler(const GameHandler&) = delete;
    GameHandler& operator=(const GameHandler&) = delete;

    // Destructor
    // Elimina la memoria reservada para los thread sender y receiver
    ~GameHandler();

    // Inicializa los thread sender y receiver
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // CONNECTION_HANDLER_H
