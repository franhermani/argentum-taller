#ifndef GAME_INPUT_HANDLER_H
#define GAME_INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "../../common/thread.h"
#include "../../common/blocking_queue.h"
#include "../../common/defines/commands.h"
#include "map_monitor.h"
#include "game_render.h"

class GameInputHandler {
    BlockingQueue<CommandDTO *> &commandQueue;
    MapMonitor &mapMonitor;
    GameRender *gameRender;

    int isLeftClick(SDL_Event &event);
    int isMoveKey(SDL_Event& event);
    void waitForLeftClick(int &x, int &y);


    CommandDTO* handleEquip();
    CommandDTO* handleUnequip();
    CommandDTO* handleHeal();
    CommandDTO* handleList();
    CommandDTO* handleTake();
    CommandDTO* handleThrow();
    CommandDTO* handleRevive();
    CommandDTO* handleDeposit();
    CommandDTO* handleSell();
    CommandDTO* handleWithdraw();
    CommandDTO* handleBuy();
    CommandDTO* handleAttack();
    CommandDTO* handleMeditate();
    CommandDTO* handleMove(moveDirection direction);


public:
    // Constructor
    GameInputHandler(BlockingQueue<CommandDTO *> &commandQueue,
                     MapMonitor &mapMonitor, GameRender *gameRender);

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
};

#endif // GAME_INPUT_HANDLER_H
