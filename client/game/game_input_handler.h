#ifndef GAME_INPUT_HANDLER_H
#define GAME_INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "../../common/thread.h"
#include "../../common/blocking_queue.h"
#include "../../common/defines/commands.h"
#include "client_world_monitor.h"
#include "game_render.h"

class GameInputHandler {
    BlockingQueue<CommandDTO *> &commandQueue;
    ClientWorldMonitor &worldMonitor;
    GameRender *gameRender;



public:
    // Constructor
    GameInputHandler(BlockingQueue<CommandDTO *> &commandQueue,
                     ClientWorldMonitor &worldMonitor, GameRender *gameRender);

    // Destructor
    ~GameInputHandler();

    // Constructor y asignacion por copia deshabilitados
    GameInputHandler(const GameInputHandler &) = delete;

    GameInputHandler &operator=(const GameInputHandler &) = delete;

    //ciclo de interaccion con teclado
    void play();

    // Inicializa los thread sender y receiver
    void run();

    // Setea la variable booleana 'keepRunning' en false
    void stop();

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead();

    // Devuelve true si hubo click izquierdo
    int isLeftClick(SDL_Event &event);

    // Devuelve true si se apreto alguna flecha
    int isMoveKey(SDL_Event& event);

    // Espera a click izq y pone en x,y sus coordenadas
    void waitForLeftClick(int &x, int &y);
};

#endif // GAME_INPUT_HANDLER_H
