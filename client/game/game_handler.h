#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <string>
#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/blocking_queue.h"
#include "../../common/utilities/json_parser.h"
#include "../communication/connection_sender.h"
#include "../communication/connection_receiver.h"
#include "game_render.h"
#include "game_input_handler.h"
#include "../../common/utilities/file.h"

class GameHandler {
    Socket socket;

    // Send related classes
    ConnectionSender* connectionSender;
    GameInputHandler* inputHandler;
    BlockingQueue<CommandDTO*> commandQueue;

    // Receive related classes
    ConnectionReceiver* connectionReceiver;
    MapMonitor mapMonitor;
    GameRender* gameRender;

    //File worldFile;


    // Hace el chequeo del username en el mismo constructor
    // Si hay un error, lanza la excepcion para que luego el main
    // la catchee y muestre un mensaje apropiado por pantalla
    // Si esta ok, sigue la ejecucion normal
    void checkUsername();

    // Imprime por pantalla un mensaje indicando que el juego va a comenzar
    void printStartMessage();

public:
    // Constructor
    GameHandler(const char *host, const char *port,
            const std::string& username, const uint8_t race_type,
            const uint8_t class_type);

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
