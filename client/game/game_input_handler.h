#ifndef GAME_INPUT_HANDLER_H
#define GAME_INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "../../common/thread.h"
#include "../../common/blocking_queue.h"
#include "../../common/defines/commands.h"
#include "map_monitor.h"

class GameInputHandler : public Thread {
    BlockingQueue<CommandDTO*>& commandQueue;
    MapMonitor& mapMonitor;

public:
    // Constructor
    GameInputHandler(BlockingQueue<CommandDTO*>& commandQueue, MapMonitor& mapMonitor);

    // Destructor
    ~GameInputHandler();

    // Constructor y asignacion por copia deshabilitados
    GameInputHandler(const GameInputHandler &) = delete;
    GameInputHandler &operator=(const GameInputHandler &) = delete;

    //ciclo de interaccion con teclado
    void play();

    // Inicializa los thread sender y receiver
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // GAME_INPUT_HANDLER_H
