#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/blocking_queue.h"
#include "../communication/connection_sender.h"
#include "../communication/connection_receiver.h"
#include "game_render.h"
#include "game_input_handler.h"

class GameHandler {
    Socket socket;

    // Send related classes
    ConnectionSender* connectionSender;
    GameInputHandler* inputHandler;
    BlockingQueue<CommandDTO*> commandQueue;

    // Receive related classes
    ConnectionReceiver* connectionReceiver;
    GameRender gameRender;
    MapMonitor mapMonitor;

public:
    // Constructor
    GameHandler(const char *host, const char *port, const char *username);

    // Constructor y asignacion por copia deshabilitados
    GameHandler(const GameHandler&) = delete;
    GameHandler& operator=(const GameHandler&) = delete;

    // Destructor
    // Elimina la memoria reservada para los thread sender y receiver
    ~GameHandler();

    // Inicializa los thread sender y receiver
    void run();

    // Setea la variable booleana 'keepRunning' en false
    void stop();

    void render_test_window();
};

#endif // CONNECTION_HANDLER_H
